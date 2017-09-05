#ifndef STANDARDTREEITEM_H
#define STANDARDTREEITEM_H


#include <QList>
#include <QVariant>

//! [0]
class StandardTreeItem
{
public:
    explicit StandardTreeItem(const QList<QVariant> &data, StandardTreeItem *parentItem = 0);
    ~StandardTreeItem();

    void appendChild(StandardTreeItem *child);

    StandardTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    StandardTreeItem *parentItem();

private:
    QList<StandardTreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    StandardTreeItem *m_parentItem;
};
//! [0]



#endif // STANDARDTREEITEM_H
