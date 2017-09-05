#include "standardtreemodel.h"
#include <QFile>
#include <QStack>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QLayout>
#include <QtWidgets>

namespace {
const qint32 MagicNumber = 0x505243;
const qint16 FormatNumber = 100;
}

StandardTreeModel::StandardTreeModel(QObject *parent)
    : QStandardItemModel(parent)
{
    initialize();
}


void StandardTreeModel::initialize()
{
    setHorizontalHeaderLabels(QStringList() << tr("Группа/Наименование")
            << tr("Цена, руб.") << tr("Цена 2, руб."));
    for (int column = 1; column < columnCount(); ++column)
        horizontalHeaderItem(column)->setTextAlignment(
                Qt::AlignVCenter|Qt::AlignLeft);

    dialog = new GroupPrice_Dialog;

    connect(dialog,SIGNAL(service_pb_clicked()),this,SLOT(add_service_row()));
    connect(dialog,SIGNAL(group_pb_clicked()),this,SLOT(add_group_row()));

}

void StandardTreeModel::take_parent_row(int parent_row)
{
    qDebug() << " дочерних - " << item(parent_row)->rowCount();
    QStandardItemModel *group_model = new QStandardItemModel;
    group_model->setHorizontalHeaderLabels(QStringList() << tr("Группа/Наименование")
                                           << tr("Цена, руб.") << tr("Цена 2, руб."));
    for(int i = 0; i < item(parent_row)->rowCount(); i++)
    {
        QList<QStandardItem*> items;
        for (int col = 0; col < 3; col ++)
        {
            items << new QStandardItem(item(parent_row)->child(i,col)->text());

        }
        group_model->appendRow(items);

    }
    send_child_model(group_model);

}


void StandardTreeModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}
void StandardTreeModel::add_new_service(int parent_row, QStringList data)
{
    QList<QStandardItem*> items;
    items << new QStandardItem(data.at(0));
    items << new QStandardItem(data.at(1));
    items << new QStandardItem(data.at(1));
    item(parent_row)->appendRow(items);

}

void StandardTreeModel::load(const QString &filename)
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

    bool is_parent;
    QString group;
    QString name_use;
    double price_one;
    double price_two;
    in >> is_parent;

    int i = 0;
    while(!in.atEnd())
    {
        i++;
        in >> group;
        QStandardItem *parent = new QStandardItem(group);
        while(!in.atEnd())
        {

            in >> is_parent;
            if (is_parent)
            {
                break;
            }

            in >> group;
            in >> price_one;
            in >> price_two;
            QList<QStandardItem*> items;
            items << new QStandardItem(group);
            items << new QStandardItem(QString::number(price_one));
            items << new QStandardItem(QString::number(price_two));
            parent->appendRow(items);

        }
        if (is_parent)
        {
            QList<QStandardItem*> items;
            items << parent;
            QStandardItem *item1 = new QStandardItem("");
            item1->setEditable(false);
            QStandardItem *item2 = new QStandardItem("");
            item2->setEditable(false);
            items << item1;
            items << item2;

            appendRow(items);

        }
        else
        {
            appendRow(parent);
        }

    }
    file.close();

}

void StandardTreeModel::add_row()
{
    if ((current_row == -2)&&(parent_row == -2))
        add_group_row();
    else
        dialog->exec();
}
void StandardTreeModel::add_group_row()
{
    dialog->done(0);

    QList<QStandardItem*> items;
    items << new QStandardItem("Новая группа");

    QStandardItem *item1 = new QStandardItem("");
    QStandardItem *item2 = new QStandardItem("");

    item1->setEditable(false);
    item2->setEditable(false);

    items << item1 << item2;

    appendRow(items);



}
void StandardTreeModel::add_service_row()
{
    dialog->done(0);

    QList<QStandardItem*> items;
    items << new QStandardItem("Новая услуга");
    items << new QStandardItem(QString::number(0.0));
    items << new QStandardItem(QString::number(0.0));
    if(parent_row == -1)
        item(current_row)->appendRow(items);
    else
        item(parent_row)->appendRow(items);
    expandall();
}

void StandardTreeModel::set_current_index(QModelIndex selected_index)
{
    parent_row = selected_index.parent().row();
    current_row = selected_index.row();

    qDebug() << parent_row << current_row;
}

void StandardTreeModel::save(const QString &filename)
{
    m_filename = filename;
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);
    bool convert;
    double d_price;
    double bad_price = 0.0;
    out << MagicNumber << FormatNumber;

    for (int row = 0; row < rowCount(); ++row) {
        out << true;
        out << data(index(row,0)).toString();
        if (item(row)->hasChildren())
            for (int child_row = 0; child_row < item(row)->rowCount(); child_row++)
            {
                out << false;
                QString price;

                out << data(index(child_row,0,index(row,0))).toString();
                price = data(index(child_row,1,index(row,0))).toString();
                price.replace(',','.');
                d_price = price.toDouble(&convert);
                if (convert)
                    out << d_price;
                else
                    out << bad_price;
                price = data(index(child_row,2,index(row,0))).toString();
                price.replace(',','.');
                d_price = price.toDouble(&convert);
                if (convert)
                    out << d_price;
                else
                    out << bad_price;
            }


    }

    file.close();
}

GroupPrice_Dialog::GroupPrice_Dialog()
{
    QVBoxLayout *vertical_layout = new QVBoxLayout;
    QHBoxLayout *horizontal_layout = new QHBoxLayout;

    QLabel *text_message  = new QLabel("Создать новую <Группу> или <Услугу>?");
    QPushButton *group_pb = new QPushButton("Группа");
    QPushButton *service_pb = new QPushButton("Услуга");

    vertical_layout->addWidget(text_message);
    horizontal_layout->addWidget(group_pb);
    horizontal_layout->addWidget(service_pb);
    vertical_layout->addLayout(horizontal_layout);

    connect(group_pb,SIGNAL(clicked(bool)),this,SIGNAL(group_pb_clicked()));
    connect(service_pb,SIGNAL(clicked(bool)),this,SIGNAL(service_pb_clicked()));

    setLayout(vertical_layout);
}
