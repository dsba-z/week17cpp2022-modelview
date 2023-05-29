#ifndef MYPROXY_H
#define MYPROXY_H

#include <QSortFilterProxyModel>

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit MyProxy(QObject *parent = nullptr);

    void setMinAge(int minAge);
    bool ageFitsFilter(QVariant dataAge) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    int _minAge;
    int _maxAge;
};

#endif // MYPROXY_H
