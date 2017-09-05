#ifndef STANDARDTABLEMODEL_H
#define STANDARDTABLEMODEL_H

#include <QDate>
#include <QStandardItemModel>
#include <QVector>

struct Hand 
{
    QString name;
    QString adress;
    int unp;
    QString bank_account;
    QString bank_name;
    QString bank_adress;
    int bank_code;
    QString nds;
    QString tax;
    QString target;
    QString order;
    QString warranty;
    QString deadline;
};
struct Contragent
{
    QString name;
    QString adress;
    int unp;
    QString bank_account;
    QString bank_name;
    QString bank_adress;
    int bank_code;
    QString person_name;
    QString person_post;
    QString dogovor;
    QString dogovor_date;
};
struct Act
{
    int number;
    QDate date;
};
struct Tn
{
    int number;
    QDate date;
    QString person;
};
class StandardTableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit StandardTableModel(QObject *parent=0, int button=0);

    QString filename() const { return m_filename; }
    void clear();
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());
    int get_max_price();
    int get_min_price();
    QDate get_min_date(){return min_date;}
    QDate get_max_date(){return max_date;}

    //модель хранения услуг для отображения
    QMap<int,QStandardItemModel*> pricemodel;
    QMap<int,Hand> hand;
    QMap<int,Contragent> contragent;
    QMap<int,Act> act;
    QMap<int,Tn> tn;

private:

    int button_model;
    void initialize();
    float max_price_model = -1;
    float min_price_model = -1;
    QString m_filename;
    QDate min_date;
    QDate max_date;


};



#endif // STANDARDTABLEMODEL_H
