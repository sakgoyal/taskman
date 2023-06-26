#pragma once
#include <QAbstractTableModel>
#include <QList>

struct Contact {
    QString name;
    QString address;

	bool operator==(const Contact &other) const { return name == other.name && address == other.address; }
};

inline QDataStream &operator<<(QDataStream &stream, const Contact &contact) { return stream << contact.name << contact.address; }

inline QDataStream &operator>>(QDataStream &stream, Contact &contact) { return stream >> contact.name >> contact.address; }

class TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr): QAbstractTableModel(parent) {}
    TableModel(const QList<Contact> &contacts, QObject *parent = nullptr) : QAbstractTableModel(parent), contacts(contacts)
    { }

    int rowCount(const QModelIndex &parent) const override{
        return parent.isValid() ? 0 : contacts.size();
    }
    int columnCount(const QModelIndex &parent) const override{
        return parent.isValid() ? 0 : 2;
    }
    QVariant data(const QModelIndex &index, int role) const override{
        if (!index.isValid())
            return QVariant();

        if (index.row() >= contacts.size() || index.row() < 0)
            return QVariant();

        if (role == Qt::DisplayRole) {
            const auto &contact = contacts.at(index.row());

            switch (index.column()) {
            case 0:
                return contact.name;
            case 1:
                return contact.address;
            default:
                break;
            }
        }
        return QVariant();
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override{
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Address");
            default:
                break;
            }
        }
        return QVariant();
    }
    Qt::ItemFlags flags(const QModelIndex &index) const override{
        if (!index.isValid())
            return Qt::ItemIsEnabled;

        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override{
        if (index.isValid() && role == Qt::EditRole) {
            const int row = index.row();
            auto contact = contacts.value(row);

            switch (index.column()) {
            case 0:
                contact.name = value.toString();
                break;
            case 1:
                contact.address = value.toString();
                break;
            default:
                return false;
            }
            contacts.replace(row, contact);
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

            return true;
        }

        return false;
    }
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override{
        Q_UNUSED(index);
        beginInsertRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row)
            contacts.insert(position, { QString(), QString() });

        endInsertRows();
        return true;
    }
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override{
        Q_UNUSED(index);
        beginRemoveRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row)
            contacts.removeAt(position);

        endRemoveRows();
        return true;
    }
	const QList<Contact> &getContacts() const { return contacts; }


private:
    QList<Contact> contacts;
};
