#include <QStringList>

#include "standardtreeitem.h"


StandardTreeItem::StandardTreeItem(const QList<QVariant> &data, StandardTreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

StandardTreeItem::~StandardTreeItem()
{
    qDeleteAll(m_childItems);
}

void StandardTreeItem::appendChild(StandardTreeItem *item)
{
    m_childItems.append(item);
}

StandardTreeItem *StandardTreeItem::child(int row)
{
    return m_childItems.value(row);
}

int StandardTreeItem::childCount() const
{
    return m_childItems.count();
}

int StandardTreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant StandardTreeItem::data(int column) const
{
    return m_itemData.value(column);
}

StandardTreeItem *StandardTreeItem::parentItem()
{
    return m_parentItem;
}

int StandardTreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<StandardTreeItem*>(this));

    return 0;
}

