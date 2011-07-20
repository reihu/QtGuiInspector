#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../src/QtGuiInspector.h"

MainWindow::MainWindow(QWidget *parent):
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
    ui->setupUi(this);

	connect(ui->actionShow, SIGNAL(triggered()), this, SLOT(showTree()));
	connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteButton()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::deleteButton() {
	if (!ui->deleteButton) {
		qWarning("Trying to delete an already deleted button, aborting...");
		return;
	}
	delete ui->deleteButton;
	ui->deleteButton = 0;

}

void MainWindow::showTree() {
	QtGuiInspector *tree = new QtGuiInspector(this);
	tree->show();
}
