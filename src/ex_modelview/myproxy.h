#ifndef MYPROXY_H
#define MYPROXY_H

#include <QSortFilterProxyModel>

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit MyProxy(QObject* parent = nullptr);
    bool filterAcceptsRow(int sourceRow, const QModelIndex& parent) const override;

// public slots:
    void setMaxFilterValue(int value);

private:
    int minFilterValue;
    int maxFilterValue;
};

#endif// MYPROXY_H
