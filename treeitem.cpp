#include "treeitem.h"

//Конструктор используется только для записи родительского элемента и данных, связанных с каждой колонкой.
TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

//деструктор
TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

//добавление дочернего элемента
void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

//возвращает дочерний элемент по индексу строки "row"
TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

//возвращает количество дочерних элементов (используется в TreeItem, для определения строк для дочерних элементов)
int TreeItem::childCount() const
{
    return m_childItems.count();
}

//количество столбцов
int TreeItem::columnCount() const
{
    return m_itemData.count();
}

//возвращает данные столбца
QVariant TreeItem::data(int column) const
{
    return m_itemData.value(column);
}

//возвращает родителя (конревой элемент возвратит 0)
TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

//Функция сообщает о расположении элемента в пределах его родительского списка
int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
