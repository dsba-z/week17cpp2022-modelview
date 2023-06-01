#include "examplemodel.h"
#include <QFile>
#include <QTextStream>

ExampleModel::ExampleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("ID");
    _header.append("Survived");
    _header.append("PClass");
    _header.append("Name");
    _header.append("Sex");
    _header.append("Age");
    _header.append("SibSp");
    _header.append("Parch");
    _header.append("Ticket");
    _header.append("Fare");
    _header.append("Cabin");
    _header.append("Embarked");

}

QVariant ExampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return _header[section];
        }
    }
    return QVariant();
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

    return _header.size();
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
        if (0 <= row && row < rowCount() && 0 <= column && columnCount())
        {
            _data[row][column] = value;
            emit dataChanged(index, index, {role});
            return true;
        }
        
        return false;
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

    // header
    QString firstline = inputStream.readLine();
    // _header = firstline.split(",");

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        QList<QString> items = line.split(",");
        for (int i = 0; i < items.size(); ++i)
        {
            QVariant value;
            if (i == 0 || i == 5)
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

bool ExampleModel::saveDataToFile(const QString& path)
{

    QFile outputFile(path);
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    QTextStream outputStream(&outputFile);



    for (const QList<QVariant>& row: _data)
    {
        bool first = true;
        for (const QVariant& item: row)
        {
            if (!first)
            {
                outputStream << ",";
            }
            outputStream << item.toString();
            first = false;
        }
    }
    return true;
}

void ExampleModel::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}


bool ExampleModel::removeRow(int rowIndex)
{
    if (rowIndex >= _data.size())
    {
        return false;
    }
    beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
    _data.removeAt(rowIndex);
    endRemoveRows();
    return true;
}
