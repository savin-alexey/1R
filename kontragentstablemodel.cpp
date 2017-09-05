#include "kontragentstablemodel.h"

#include "global.h"
#include <QFile>
#include <QDebug>
#include <QDate>



namespace {
const qint32 MagicNumber = 0x4B4F4E;
const qint16 FormatNumber = 100;
}

KontragentsTableModel::KontragentsTableModel(QObject *parent)
    : QStandardItemModel(parent)
{
    initialize();
}

void KontragentsTableModel::initialize()
{
        setHorizontalHeaderLabels(QStringList()
                                  << tr("Название")
                                  << tr("Адрес")
                                  << tr("УНП")
                                  << tr("ОКПО")
                                  << tr("Расчётный счёт")
                                  << tr("Банк")
                                  << tr("Адрес банка")
                                  << tr("Код")
                                  << tr("Страна")
                                  << tr("Договор")
                                  << tr("Дата договора")
                                  );

}

void KontragentsTableModel::edit(QModelIndex selected_index)
{
    QStringList rowData;
    QString myData;
    myData = selected_index.model()->data( selected_index.model()->index(selected_index.row(),0,QModelIndex()), Qt::DisplayRole).toString();

    for (int i = 0; i < rowCount(); i++)
    {
        if(index(i,0).data().toString() == myData)
        {
            edit_row = i;
            break;
        }
    }
    qDebug() << edit_row;

    for(int i = 0; i < columnCount(); i++)
        rowData << data(index(edit_row,i)).toString();
    if(leadership.contains(data(index(edit_row,0)).toString()))
        rowData << leadership[data(index(edit_row,0)).toString()];
    key = rowData.at(0);
    send_item(rowData);


}
void KontragentsTableModel::take_edit(QStringList edit_data)
{
    leadership.remove(key);
    for(int i = 0; i < columnCount(); i++)
        setData(index(edit_row,i),edit_data.at(i));
    for(int i = columnCount(); i < edit_data.count(); i++)
        leadership[edit_data.at(0)] << edit_data.at(i);
}

void KontragentsTableModel::add_new(QStringList datalist)
{
    qDebug() << "Добавлено: "<<datalist;
    QMap<QString, QList<QStandardItem*> > itemsfortable;

    QList<QStandardItem*> items;
    QStandardItem *item = new QStandardItem;
    item->setData(datalist.at(0), Qt::DisplayRole);
    items << item;
    foreach (const QString &text, QStringList()

             << datalist.at(1)
             << datalist.at(2)
             << datalist.at(3)
             << datalist.at(4)
             << datalist.at(5)
             << datalist.at(6)
             << datalist.at(7)
             << datalist.at(8)
             << datalist.at(9)
             << datalist.at(10)
                )
        items << new QStandardItem(text);

        for (int i = 11; i < datalist.size(); i ++ )
            leadership[datalist.at(0)] << datalist.at(i);



    itemsfortable[datalist.at(0)] = items;

    QMapIterator<QString, QList<QStandardItem*> > i(itemsfortable);
    while (i.hasNext())
        appendRow(i.next().value());


}

void KontragentsTableModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}
void KontragentsTableModel::load(const QString &filename)
{

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

    QString name;
    QString adress;
    QString unp;
    QString okpo;
    QString bank_account;
    QString bank_name;
    QString bank_adress;
    int bank_code;
    QString country;
    QString dogovor;
    QDate dogovor_date;
    bool have_leadership;

    QMap<QString, QList<QStandardItem*> > itemsfortable;
    while(!in.atEnd())
    {
        in  >> name
            >> adress
            >> unp
            >> okpo
            >> bank_account
            >> bank_name
            >> bank_adress
            >> bank_code
            >> country
            >> dogovor
            >> dogovor_date
            >> have_leadership;
        QList<QStandardItem*> items;
        QStandardItem *item = new QStandardItem;
        item->setData(name, Qt::DisplayRole);
        items << item;
        foreach (const QString &text, QStringList()

                 << adress
                 << unp
                 << okpo
                 << bank_account
                 << bank_name
                 << bank_adress
                 << QString::number(bank_code)
                 << country
                 << dogovor
                 << dogovor_date.toString("dd.MM.yyyy")
                 )
        items << new QStandardItem(text);


        itemsfortable[name] = items;
        while (have_leadership)
        {
            QString post, post_name;
            in >> post >> post_name;
            leadership[name]<< post << post_name ;
            in >> have_leadership;
        }

    }
    QMapIterator<QString, QList<QStandardItem*> > i(itemsfortable);
    while (i.hasNext())
        appendRow(i.next().value());

    qDebug() << leadership;
    file.close();


}
void KontragentsTableModel::take_new_person(int row, QString name, QString post)
{
    leadership[index(row,0).data().toString()] << name;
    leadership[index(row,0).data().toString()] << post;
}

void KontragentsTableModel::save(const QString &filename)
{
    m_filename = filename;
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);


    out << MagicNumber << FormatNumber;

    for (int row = 0; row < rowCount(); ++row) {
        out << static_cast<QString>(item(row, 0)->data(Qt::DisplayRole).toString())
            << item(row, 1)->text()
            << item(row, 2)->text()
            << item(row, 3)->text()
            << item(row, 4)->text()
            << item(row, 5)->text()
            << item(row, 6)->text()
            << item(row, 7)->text().toInt()
            << item(row, 8)->text()
            << item(row, 9)->text()
            << QDate::fromString(item(row, 10)->text(),"dd.MM.yyyy");
            for(int i = 0; i < leadership[data(index(row,0)).toString()].size(); i = i+2)
            {
                out << true;
                out << leadership[data(index(row,0)).toString()].at(i);
                out << leadership[data(index(row,0)).toString()].at(i+1);
            }
            out << false;

    }

   /* QString name = "Верховичский крахмальный завод, ОАО";
    QString adress = "225074, Брестская обл., Каменецкий р-н, дер.Верховичи";
    QString unp = "200193428";
    QString okpo = "";
    QString bank_account = "3012200530014";
    QString bank_name = "Отд. ОАО БелАПБ в г.Каменец";
    QString bank_adress = "225051, Брестская обл., г.Каменец, ул.Брестская, 3";
    int bank_code = 410;
    QString country = "Беларусь";
    QString dogovor = "002";
    QDate dogovor_date;
    dogovor_date.setDate(2005,06,21);
    bool have_leadership = true;
    QString post_name = "Савчук Н.П.";
    QString post = "Директор";

    out << MagicNumber
        << FormatNumber
        << name
        << adress
        << unp
        << okpo
        << bank_account
        << bank_name
        << bank_adress
        << bank_code
        << country
        << dogovor
        << dogovor_date
        << have_leadership
        << post
        << post_name;

*/
    file.close();
}
QStringList KontragentsTableModel::take_leadership(QString name)
{
    return leadership[name];
}
