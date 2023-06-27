#pragma once
#include "tablemodel.hpp"
#include </usr/include/proc/procps.h>
#include <QItemSelection>
#include <QStandardPaths>
#include <QTabWidget>
#include <QWidget>
#include <QtWidgets>
#include <fmt/format.h>
#include <iostream>
#include "processesWidget.hpp"
QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

class AddressWidget: public QTabWidget {
	Q_OBJECT

public:
	AddressWidget(QWidget *parent = nullptr): QTabWidget(parent) {
		for (const QString &title: tabTitles) {
			QWidget *tab = new QWidget(this);
			processesWidget = new ProcessesWidget(tab);
			this->addTab(processesWidget, title);
		}
			
		// 	QStandardItemModel* model = new QStandardItemModel(0, 6, tab);
			
		// 	tableView->setFixedWidth(500);
		// 	tableView->setSortingEnabled(true);
		// 	tableView->verticalHeader()->hide();
		// 	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		// 	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		// 	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
			
		// 	tableView->horizontalHeader()->setStretchLastSection(true);
		// 	tableView->horizontalHeader()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		// 	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
		// 	tableView->horizontalHeader()->setSectionsMovable(true);
		// 	tableView->horizontalHeader()->setDragEnabled(true);
		// 	// tableView->horizontalHeader()->setScrollMode(QHeaderView::ScrollPerPixel);
			
		// 	for (int column = 0; column < headers.size(); ++column) {
		// 		model->setHeaderData(column, Qt::Horizontal, headers[column]);
		// 	}

		// 	tableView->setModel(model);
		// 	this->addTab(tab, title);
		// 	connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AddressWidget::selectionChanged);
		// 	connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
		// 		 if (widget(tabIndex) == tableView) emit selectionChanged(tableView->selectionModel()->selection());
		//  	});
		// }
	}

public slots:
	void showAddEntryDialog() { }
	void addEntry(const QString &name, const QString &address) { }
	void editEntry() {}
	void removeEntry() {}

  signals:
	void selectionChanged(const QItemSelection &selected);

  private:
	const std::vector<QString> tabTitles = {"Processes", "Performance", "Startup", "Users", "Details", "Services"};
	ProcessesWidget *processesWidget;
};