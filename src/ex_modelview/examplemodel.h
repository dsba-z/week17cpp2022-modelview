#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <QAbstractTableModel>

class ExampleModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ExampleModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool reloadDataFromFile(const QString& path);
    bool saveDataToFile(const QString& path);
    
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void appendRow(const QList<QVariant>& newRow);
    bool removeRow(int rowIndex);

private:

    QList<QList<QVariant>> _data;
    QList<QString> _header;
};

#endif // EXAMPLEMODEL_H
