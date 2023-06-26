// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#pragma once
#include <QWidget>
#include "adddialog.hpp"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class NewAddressTab : public QWidget {
    Q_OBJECT

public:
	NewAddressTab(QWidget *parent = nullptr){
		auto descriptionLabel = new QLabel("There are currently no contacts in your address book. "
										   "\nClick Add to add new contacts.");

		auto addButton = new QPushButton("Add");
		connect(addButton, &QAbstractButton::clicked, this, &NewAddressTab::addEntry);
		auto mainLayout = new QVBoxLayout;
		mainLayout->addWidget(descriptionLabel);
		mainLayout->addWidget(addButton, 0, Qt::AlignCenter);
		setLayout(mainLayout);
	}

public slots:
	void addEntry(){
		AddDialog aDialog;

		if (aDialog.exec()) emit sendDetails(aDialog.name(), aDialog.address());
	}


signals:
    void sendDetails(const QString &name, const QString &address);
};
