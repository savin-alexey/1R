#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>


class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent=0);

    float minimumPrice() const { return m_minimumPrice; }
    float maximumPrice() const { return m_maximumPrice; }
    QString client() const { return m_client; }
    //QString state() const { return m_state; }

public slots:
    void clearFilters();
    void setMinimumPrice(float minimumPrice);
    void setMaximumPrice(float maximumPrice);
    void setClient(const QString &client);
    void setDate(const QDate &date);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;

private:
    float m_minimumPrice;
    float m_maximumPrice;
    QString m_client;
    QDate m_date;
};


#endif // PROXYMODEL_H
