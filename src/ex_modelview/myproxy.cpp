#include "myproxy.h"

MyProxy::MyProxy(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    _minAge = 0;
    _maxAge = 30;
}

void MyProxy::setMinAge(int minAge)
{
    this->_minAge = minAge;
    invalidateFilter();
}

bool MyProxy::ageFitsFilter(QVariant dataAge) const
{
    return (_minAge < dataAge.toInt() && dataAge.toInt() < _maxAge);
}

bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex indexAge = sourceModel()->index(sourceRow, 5, sourceParent);

    QVariant data0 = sourceModel()->data(index0);
    bool accepts0 = data0.toString().contains(filterRegularExpression());

    QVariant dataAge = sourceModel()->data(indexAge);
    bool acceptsAge = ageFitsFilter(dataAge);
    return accepts0 && acceptsAge;
}
