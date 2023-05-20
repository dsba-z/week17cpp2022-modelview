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
    
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void appendRow(const QList<QVariant>& newRow);
    void removeRow(int rowIndex);

private:

    QList<QList<QVariant>> _data;
};

#endif // EXAMPLEMODEL_H
