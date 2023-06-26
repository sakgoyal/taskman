#pragma once
#include "addresswidget.hpp"

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

//! [0]
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	MainWindow() : QMainWindow(), addressWidget(new AddressWidget) {
        setCentralWidget(addressWidget);
        createMenus();
		setWindowTitle("KTaskman");
    }

private slots:
	void updateActions(const QItemSelection &selection){
		QModelIndexList indexes = selection.indexes();

		if (!indexes.isEmpty()) {
			removeAct->setEnabled(true);
			editAct->setEnabled(true);
		} else {
			removeAct->setEnabled(false);
			editAct->setEnabled(false);
		}
	}
	void openFile() { addressWidget->readFromFile(); }
	void saveFile() { addressWidget->writeToFile(); }


private:
	void createMenus(){
		QMenu *fileMenu = menuBar()->addMenu("&File");

		QAction *openAct = new QAction("&Open...", this);
		fileMenu->addAction(openAct);
		connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
		QAction *saveAct = new QAction("&Save", this);
		fileMenu->addAction(saveAct);
		connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

		fileMenu->addSeparator();

		QAction *exitAct = new QAction("E&xit", this);
		fileMenu->addAction(exitAct);
		connect(exitAct, &QAction::triggered, this, &QWidget::close);

		QMenu *toolMenu = menuBar()->addMenu("&Tools");

		QAction *addAct = new QAction("&Add Entry...", this);
		toolMenu->addAction(addAct);
		connect(addAct, &QAction::triggered, addressWidget, &AddressWidget::showAddEntryDialog);
		editAct = new QAction("&Edit Entry...", this);
		editAct->setEnabled(false);
		toolMenu->addAction(editAct);
		connect(editAct, &QAction::triggered, addressWidget, &AddressWidget::editEntry);

		toolMenu->addSeparator();

		removeAct = new QAction("&Remove Entry", this);
		removeAct->setEnabled(false);
		toolMenu->addAction(removeAct);
		connect(removeAct, &QAction::triggered, addressWidget, &AddressWidget::removeEntry);

		connect(addressWidget, &AddressWidget::selectionChanged, this, &MainWindow::updateActions);
	}

    AddressWidget *addressWidget;
    QAction *editAct;
    QAction *removeAct;
};
