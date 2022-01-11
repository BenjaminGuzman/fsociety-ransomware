#define SAFE_MODE true // if true, no encryption and the app can be closed
#include "mainwindow.h"

#include <QApplication>
#include <csignal>
#include <iostream>

void signalHandler(int signum) {
	std::cout << "🖕💀🔥💀🔥💀🔥🖕" << std::endl;
}

int main(int argc, char *argv[])
{
#if SAFE_MODE
	std::cout << "Using safe mode 🦺, no files will be encrypted and window can be closed" << std::endl;
#endif
	// catch signals
	std::array<int, 5> sigs = {SIGINT, SIGTERM, SIGHUP, SIGUSR1, SIGUSR2};
	for (int sig : sigs)
		signal(sig, signalHandler);

	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowState(Qt::WindowFullScreen);
	w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);
	w.show();
	return a.exec();
}
