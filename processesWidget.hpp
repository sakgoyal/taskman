#pragma once

#include "tablemodel.hpp"
#include </usr/include/proc/procps.h>
#include <QItemSelection>
#include <QWidget>
#include <QtWidgets>
#include <QVBoxLayout>
#include <fmt/format.h>
#include <iostream>


QT_BEGIN_NAMESPACE
class QItemSelectionModel;
QT_END_NAMESPACE


class ProcessesWidget : public QWidget {
	Q_OBJECT

public:
	ProcessesWidget(QWidget *parent=nullptr){
		QWidget *tab = new QWidget(parent);
		QTableView *tableView = new QTableView(tab);
		QStandardItemModel* model = new QStandardItemModel(0, 6, tab);
		
		tableView->setFixedWidth(500);
		tableView->setSortingEnabled(true);
		tableView->verticalHeader()->hide();
		tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		
		tableView->horizontalHeader()->setStretchLastSection(true);
		tableView->horizontalHeader()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
		tableView->horizontalHeader()->setSectionsMovable(true);
		tableView->horizontalHeader()->setDragEnabled(true);
		// tableView->horizontalHeader()->setScrollMode(QHeaderView::ScrollPerPixel);
		
		for (int column = 0; column < headers.size(); ++column) {
			model->setHeaderData(column, Qt::Horizontal, headers[column]);
		}

		tableView->setModel(model);
		// connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ProcessesWidget::selectionChanged);
		// connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
		// 	 if (widget(tabIndex) == tableView) emit selectionChanged(tableView->selectionModel()->selection());
		// });
	}


public slots:
	void showAddEntryDialog() { }
	void addEntry(const QString &name, const QString &address) { }
	void editEntry() {}
	void removeEntry() {}

signals:
	void selectionChanged(const QItemSelection &selected);

private:
	TableModel *table = new TableModel(this);
	const QStringList headers = {"Name", "CPU", "Memory", "Disk", "PID", "Network"};
};