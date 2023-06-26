#pragma once
#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include "addresswidget.hpp"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	MainWindow() : QMainWindow(),addressWidget(new AddressWidget) {
        setCentralWidget(addressWidget);
        createMenus();
		setWindowTitle("KTaskman");
		// setWindowIcon(QIcon(":/images/icon.png"));
		// setUnifiedTitleAndToolBarOnMac(true);
		setMinimumSize(500, 400);
    }

private:
	void createMenus(){
		QMenu *fileMenu = menuBar()->addMenu("&File");
		QAction *openAct = new QAction("&Open...", this);
		fileMenu->addAction(openAct);
		// connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
		
		fileMenu->addSeparator();
		
		QAction *exitAct = new QAction("E&xit", this);
		fileMenu->addAction(exitAct);
		connect(exitAct, &QAction::triggered, this, &QWidget::close);

		QMenu *toolMenu = menuBar()->addMenu("&Options");
		QAction *refreshSp = new QAction("&Refresh Speed", this);
		toolMenu->addAction(refreshSp);
		// connect(refreshSp, &QAction::triggered, this, this->refreshSpAct);
		
		toolMenu->addSeparator();



		QMenu *viewMenu = menuBar()->addMenu("&View");
		viewMenu->addSeparator();


	}
    AddressWidget *addressWidget;
	QAction *editAct;
    QAction *removeAct;
	QAction *refreshSpAct;
};
