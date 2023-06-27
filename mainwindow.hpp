#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include "addresswidget.hpp"
#include <QCoreApplication>
#include <QDir>
#include <iostream>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	MainWindow() : QMainWindow(), addressWidget(new AddressWidget(this)){
		setWindowTitle("KTaskman");
		setMinimumSize(500, 400);
		createMenus(); // (File, Options, View)
		setCentralWidget(addressWidget);
		
        // setWindowIcon(QIcon(":/images/icon.png"));
    }

	std::vector<std::string> getProcList(std::string dir){
		std::vector<std::string> procList;
    	QStringList processDirs = QDir("/proc").entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    	for (auto processDir : processDirs) {
        	bool ok;
        	int pid = processDir.toInt(&ok);
        	if (ok) {
    	        QFile stat(QString("/proc/%1/stat").arg(pid));
        	    if (stat.open(QIODevice::ReadOnly)) {
            	    QString statData = stat.readLine();
                	QStringList statParts = statData.split(' ');

	                // Extract the desired process information from 'statParts' list
    	            auto processName = statParts.at(1).trimmed().toStdString();
        	        std::cout << "\nPID:" << pid << " Name:" << processName << "Dir: " << processDir.toStdString();
            	}
        	}
    	}
		return procList;
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

#endif // MAINWINDOW_HPP