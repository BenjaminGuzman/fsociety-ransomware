#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *evt) {
#if !SAFE_MODE
	evt->ignore();
#endif
}

void MainWindow::changeEvent(QEvent *evt) {
	if (evt->type() == QEvent::ActivationChange) {
		if (!this->isActiveWindow()) {
			this->activateWindow();
			this->raise();
		}
	}
}


