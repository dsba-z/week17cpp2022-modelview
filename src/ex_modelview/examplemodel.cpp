#include "examplemodel.h"
#include <QFile>
#include <QTextStream>


ExampleModel::ExampleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // for (int i = 0; i < 10; ++i)
    // {
    //     QList<QVariant> newRow;
    //     for (int j = 0; j < 5; ++j)
    //     {
    //         newRow.push_back(2);
    //     }
    //     _data.push_back(newRow);
    // }
}

bool ExampleModel::loadDataFromFile(const QString& path)
{
    QList<QList<QVariant>> newData;

    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();

    // inputStream >> a;
    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        
        QList<QVariant> dataRow;
        for (const QString& item : line.split(",")) {
            dataRow.append(item);
        }
        newData.append(dataRow);
    }
    inputFile.close();
    
    beginResetModel();
    _data = newData;
    endResetModel();
}

int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    

    return _data.size();
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();
        return _data[row][column];

    }
    else if (role == Qt::CheckStateRole)
    {
        return QVariant();
    }
    // FIXME: Implement me!
    return QVariant();
}
