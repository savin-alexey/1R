#include "proxymodel.h"
#include <QDebug>

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    m_minimumPrice = m_maximumPrice = -1;
}


void ProxyModel::clearFilters()
{
    m_minimumPrice = m_maximumPrice = -1;
    m_client.clear();
    m_date.setDate(1999,01,01);
    invalidateFilter();
}


bool ProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    if (m_minimumPrice != -1 ||
        m_maximumPrice != -1) {
        QModelIndex index = sourceModel()->index(sourceRow, 2,
                                                 sourceParent);
        if (m_minimumPrice != -1 &&
            sourceModel()->data(index).toFloat() < m_minimumPrice)
        {qDebug() << "False";
            return false;}
        if (m_maximumPrice != -1 &&
            sourceModel()->data(index).toFloat() > m_maximumPrice)
        {qDebug() << "False";
            return false;}
    }
    if (!m_client.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow, 3,
                                                 sourceParent);
        if (m_client != sourceModel()->data(index).toString())
            return false;
    }
    if (m_date.year()>2000) {
        QModelIndex index = sourceModel()->index(sourceRow, 1,
                                                 sourceParent);
        if (m_date.toString("dd.MM.yyyy") != sourceModel()->data(index).toString())
            return false;
    }
    qDebug() << "true";
    return true;
}


void ProxyModel::setMinimumPrice(float minimumPrice)
{
    if (m_minimumPrice != minimumPrice) {
        m_minimumPrice = minimumPrice;
        invalidateFilter();
    }
}


void ProxyModel::setMaximumPrice(float maximumPrice)
{
    if (m_maximumPrice != maximumPrice) {
        m_maximumPrice = maximumPrice;
        invalidateFilter();
    }
}


void ProxyModel::setClient(const QString &client)
{
    if (m_client != client) {
        m_client = client;
        invalidateFilter();
    }
}


void ProxyModel::setDate(const QDate &date)
{
    if (m_date != date) {
        m_date = date;
        invalidateFilter();
    }
}

