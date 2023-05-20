#include "examplemodel.h"
#include <QFile>
#include <QTextStream>

ExampleModel::ExampleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int ExampleModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int ExampleModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant ExampleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();
        return _data.at(row).at(column);
    }
    else if (role == Qt::CheckStateRole)
    {
        return QVariant();
    }
    return QVariant();
}

bool ExampleModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value)
    {
        int row = index.row();
        int column = index.column();
        _data[row][column] = value;

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ExampleModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool ExampleModel::reloadDataFromFile(const QString& path)
{

    QList<QList<QVariant>> newData;

    QFile inputFile(path);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);


    QString firstline = inputStream.readLine();

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        QList<QString> items = line.split(",");
        for (int i = 0; i < items.size(); ++i)
        {
            QVariant value;
            if (i == 0)
            {
                value = items[i].toInt();
            }
            else
            {
                value = items[i];
            }
            
            dataRow.append(value);
        }
        newData.append(dataRow);
    }
    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}

void ExampleModel::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}


void ExampleModel::removeRow(int rowIndex)
{
    beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
    _data.removeAt(rowIndex);
    endRemoveRows();
}