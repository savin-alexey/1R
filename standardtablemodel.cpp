#include "standardtablemodel.h"
#include "global.h"
#include <QFile>
#include <QDebug>
#include <QDate>
#include <cmath>


namespace {
const qint32 MagicNumber = 0x534346;
const qint16 FormatNumber = 100;
}

StandardTableModel::StandardTableModel(QObject *parent, int button)
    : QStandardItemModel(parent)
{
    button_model = button;
    initialize();
}

void StandardTableModel::initialize()
{

    switch (button_model) {
    case 1:
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Номер")
                                  << tr("Дата")
                                  << tr("Сумма")
                                  << tr("Контрагент")
                                  << tr("Акт")
                                  << tr("Накладные"));
        break;
    case 2:
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Номер")
                                  << tr("Дата")
                                  << tr("Сумма")
                                  << tr("Контрагент")
                                  << tr("Адрес")
                                  << tr("Реквизиты"));
        break;
    case 3:
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Номер")
                                  << tr("Дата")
                                  << tr("Сумма")
                                  << tr("Контрагент")
                                  << tr("Адрес")
                                  << tr("Реквизиты"));
        break;
    case 4:
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Номер")
                                  << tr("Название")
                                  << tr("Адрес")
                                  << tr("УНП")
                                  << tr("ОКПО")
                                  << tr("Расчётный счёт")
                                  << tr("Банк")
                                  << tr("Адрес банка")
                                  << tr("Код")
                                  << tr("Страна")
                                  << tr("Руководитель")
                                  << tr("Долгосрочный договор")
                                  );
        break;
    case 5:
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Наименование")
                                  << tr("Цена")
                                  << tr("Вторая цена"));

        break;

    }


}



void StandardTableModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}
void StandardTableModel::load(const QString &filename)
{
    /*
    m_filename = filename;
    QFile file(m_filename);
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);

    qint32 magicNumber;
    in >> magicNumber;
    if (magicNumber != MagicNumber)
        qDebug() << "magicNumber invalid";
    qint16 formatVersionNumber;
    in >> formatVersionNumber;
    if (formatVersionNumber > FormatNumber)
        qDebug() << "new file version exist";
    in.setVersion(QDataStream::Qt_5_7);
    clear();

    qint8 number2;
    QDate date;
    float summ;
    QString kontragent;
    QString adress;
    QString request;

    QMap<quint8, QList<QStandardItem*> > itemsfortable;
    while(!in.atEnd())
    {
        in >> number2 >> date >> summ >> kontragent >> adress >> request;
        QList<QStandardItem*> items;
        QStandardItem *item = new QStandardItem;
        item->setData(number2, Qt::EditRole);
        items << item;
        foreach (const QString &text, QStringList() << date.toString("dd.MM.yyyy") << QString::number(summ) << kontragent <<adress << request)
        items << new QStandardItem(text);
        itemsfortable[number2] = items;
        if (summ > max_price_model)
            max_price_model = summ;

        if (summ < min_price_model || min_price_model == -1)
            min_price_model = summ;
        if (date > max_date || max_date.isNull())
            max_date = date;
        if (date < min_date || min_date.isNull())
            min_date = date;
    }
    QMapIterator<quint8, QList<QStandardItem*> > i(itemsfortable);
    while (i.hasNext())
        appendRow(i.next().value());

    file.close();
    */

    //тестовый мусор
    QDate date2;
    date2.setDate(2017,6,6);


    QList<QStandardItem*> items;
    items << new QStandardItem("4");
    items << new QStandardItem(date2.toString("dd.MM.yyyy"));
    hand[4].name = "ИП.";




    appendRow(items);


    /*Конец тестового мусора*/

}
void StandardTableModel::save(const QString &filename)
{
    m_filename = filename;
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);
    //out << MagicNumber << FormatNumber;
    int number = 4;
    QDate date(2015,03,20);




    file.close();
}
int StandardTableModel::get_max_price()
{
    return floor(max_price_model+1);
}
int StandardTableModel::get_min_price()
{
    return floor(min_price_model);
}
