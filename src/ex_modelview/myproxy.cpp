#include "myproxy.h"

MyProxy::MyProxy(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    _minAge = 0;
    _maxAge = 30;
    _ageFilterEnabled = true;
}

void MyProxy::setMinAge(int minAge)
{
    this->_minAge = minAge;
    invalidateFilter();
}

bool MyProxy::ageFitsFilter(QVariant dataAge) const
{
    if (_ageFilterEnabled)
    {
        return _minAge <= dataAge.toInt() && dataAge.toInt() < _maxAge;
    }
    return true;
}

bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariant data0 = sourceModel()->data(index0);
    bool accepts0 = data0.toString().contains(filterRegularExpression());
    
    QModelIndex indexAge = sourceModel()->index(sourceRow, 5, sourceParent);
    QVariant dataAge = sourceModel()->data(indexAge);
    bool acceptsAge = ageFitsFilter(dataAge);

    return accepts0 && acceptsAge;
}

// bool MyProxy::lessThan(const QModelIndex &left,
//                                       const QModelIndex &right) const
// {
//     QVariant leftData = sourceModel()->data(left);
//     QVariant rightData = sourceModel()->data(right);

//     return leftData.toString() < rightData.toString();
// }