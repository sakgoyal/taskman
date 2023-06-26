#pragma once

#include <QDialog>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class AddDialog : public QDialog {
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString name() const { return nameText->text(); }
    
    QString address() const { return addressText->toPlainText(); }
    
    void editAddress(const QString &name, const QString &address) { 
        nameText->setReadOnly(true);
        nameText->setText(name);
        addressText->setPlainText(address);
    }

    void AddDialog(QWidget *parent) : QDialog(parent), nameText(new QLineEdit), addressText(new QTextEdit) {
	auto nameLabel = new QLabel("Name");
	auto addressLabel = new QLabel("Address");
	auto okButton = new QPushButton("OK");
	auto cancelButton = new QPushButton("Cancel");

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(addressLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(addressText, 1, 1, Qt::AlignLeft);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

	setWindowTitle("Add a Contact");
}
    

private:
    QLineEdit *nameText;
    QTextEdit *addressText;
};
