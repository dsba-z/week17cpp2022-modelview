#include "myproxy.h"
#include "constants.h"

MyProxy::MyProxy(QObject* parent)
{
    minFilterValue = 0;
    maxFilterValue = 20;
}

void MyProxy::setMaxFilterValue(int value)
{
    maxFilterValue = value;
    invalidateFilter();
}

bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex &parent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, Columns::Age);
    QVariant sourceData = sourceModel()->data(sourceIndex);

    if (sourceData.toInt() < maxFilterValue)
    {
        return true;
    }
    else
    {
        return false;
    }
}