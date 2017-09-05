#include "settings.h"
#include <QFile>
#include <QDebug>


Settings::Settings()
{
    load();
}
Settings::~Settings()
{
    save();
}

bool Settings::load()
{
    QFile file("settings.dat");
    if (!file.open(QIODevice::ReadOnly))
            return false;
    QDataStream in(&file);

    qint32 magicNumber;
    in >> magicNumber;
    if (magicNumber != MagicNumber)
        return false;
    qint16 formatVersionNumber;
    in >> formatVersionNumber;
    if (formatVersionNumber > FormatNumber)
        return false;
    in.setVersion(QDataStream::Qt_5_7);


    in >> data >> target >> payment_order >> warranty >> deadline;
    file.close();



    return true;
}
bool Settings::save()
{
    QFile file("settings.dat");
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);







    out << MagicNumber
        << FormatNumber
        << data
        << target
        << payment_order
        << warranty
        << deadline;

    file.close();
    return true;
}

SettingsDialog::SettingsDialog()
{
    QVBoxLayout *megatop_layout = new QVBoxLayout;
    QHBoxLayout *top_layout = new QHBoxLayout;
    QVBoxLayout *left_layout = new QVBoxLayout;
    QVBoxLayout *center_layout = new QVBoxLayout;
    QVBoxLayout *right_layout = new QVBoxLayout;
    QHBoxLayout *buttons_layout = new QHBoxLayout;

    QLabel *le_name = new QLabel("Название:");
    QLabel *le_adress = new QLabel("Адрес");
    QLabel *le_unp = new QLabel("УНП:");
    QLabel *le_bank_account = new QLabel("Р/с:");
    QLabel *le_bank_name = new QLabel("Банк:");
    QLabel *le_bank_adress = new QLabel("Адрес банка:");
    QLabel *le_bank_code = new QLabel("Код банка:");
    QLabel *le_next_tn2 = new QLabel("Номер следующей накладной:");
    QLabel *le_next_order = new QLabel("Номер следующего счёта:");
    QLabel *vac = new QLabel("НДС:");
    QLabel *gov_tax = new QLabel("Основание НДС:");

    left_layout->addWidget(le_name);
    left_layout->addWidget(le_adress);
    left_layout->addWidget(le_unp);
    left_layout->addWidget(le_bank_account);
    left_layout->addWidget(le_bank_name);
    left_layout->addWidget(le_bank_adress);
    left_layout->addWidget(le_bank_code);
    left_layout->addWidget(le_next_tn2);
    left_layout->addWidget(le_next_order);
    left_layout->addWidget(vac);
    left_layout->addWidget(gov_tax);

    for(int i = 0; i < 11; i++)
    {
        l_edit[i] = new QLineEdit;
        l_edit[i]->setMaximumWidth(250);
        l_edit[i]->setMinimumWidth(250);
        center_layout->addWidget(l_edit[i]);
    }


    QLabel *le_target = new QLabel("Цель приобретения:");
    QLabel *le_order = new QLabel("Порядок оплаты:");
    QLabel *le_warranty = new QLabel("Гарантийный срок:");
    QLabel *le_deadline = new QLabel("Срок выполнения:");
    target_view = new QListWidget;
    target_view->setMaximumHeight(70);
    order_view = new QListWidget;
    order_view->setMaximumHeight(70);
    warranty_view = new QListWidget;
    warranty_view->setMaximumHeight(70);
    deadline_view = new QListWidget;
    deadline_view->setMaximumHeight(70);

    right_layout->addWidget(le_target);
    right_layout->addWidget(target_view);
    right_layout->addWidget(le_order);
    right_layout->addWidget(order_view);
    right_layout->addWidget(le_warranty);
    right_layout->addWidget(warranty_view);
    right_layout->addWidget(le_deadline);
    right_layout->addWidget(deadline_view);




    QPushButton *save_pb = new QPushButton("Сохранить");
    QPushButton *cancel_pb = new QPushButton("Отмена");

    buttons_layout->addWidget(save_pb);
    buttons_layout->addWidget(cancel_pb);

    top_layout->addLayout(left_layout);
    top_layout->addLayout(center_layout);
    top_layout->addLayout(right_layout);



    megatop_layout->addLayout(top_layout);
    megatop_layout->addLayout(buttons_layout);

    setLayout(megatop_layout);

    connect(target_view,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(edit_list_view(QListWidgetItem*)));
    connect(target_view,SIGNAL(itemSelectionChanged()),order_view,SLOT(clearSelection()));
    connect(target_view,SIGNAL(itemSelectionChanged()),warranty_view,SLOT(clearSelection()));
    connect(target_view,SIGNAL(itemSelectionChanged()),deadline_view,SLOT(clearSelection()));

    connect(order_view,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(edit_order_view(QListWidgetItem*)));
    connect(order_view,SIGNAL(itemSelectionChanged()),target_view,SLOT(clearSelection()));
    connect(order_view,SIGNAL(itemSelectionChanged()),warranty_view,SLOT(clearSelection()));
    connect(order_view,SIGNAL(itemSelectionChanged()),deadline_view,SLOT(clearSelection()));

    connect(warranty_view,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(edit_warranty_view(QListWidgetItem*)));
    connect(warranty_view,SIGNAL(itemSelectionChanged()),order_view,SLOT(clearSelection()));
    connect(warranty_view,SIGNAL(itemSelectionChanged()),target_view,SLOT(clearSelection()));
    connect(warranty_view,SIGNAL(itemSelectionChanged()),deadline_view,SLOT(clearSelection()));

    connect(deadline_view,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(edit_deadline_view(QListWidgetItem*)));
    connect(deadline_view,SIGNAL(itemSelectionChanged()),order_view,SLOT(clearSelection()));
    connect(deadline_view,SIGNAL(itemSelectionChanged()),target_view,SLOT(clearSelection()));
    connect(deadline_view,SIGNAL(itemSelectionChanged()),warranty_view,SLOT(clearSelection()));

    QShortcut *shortcut1 = new QShortcut(QKeySequence( Qt::Key_Delete ),this);

    connect(shortcut1,SIGNAL(activated()),this,SLOT(delete_list_item()));
    connect(cancel_pb,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(save_pb,SIGNAL(clicked(bool)),this,SLOT(save_clicked()));

}
void SettingsDialog::save_clicked()
{
    QStringList data;
    QStringList target;
    QStringList payment_order;
    QStringList warranty;
    QStringList deadline;

    for(int i = 0; i < 11; i++)
    {
        data << l_edit[i]->text();
    }
    for(int i = 0; i < target_view->count(); i++)
    {
        target << target_view->item(i)->text();
    }
    for(int i = 0; i < order_view->count(); i++)
    {
        payment_order << order_view->item(i)->text();
    }
    for(int i = 0; i < warranty_view->count(); i++)
    {
        warranty << warranty_view->item(i)->text();
    }
    for(int i = 0; i < deadline_view->count(); i++)
    {
        deadline << deadline_view->item(i)->text();
    }


    send_new_data(data,target,payment_order,warranty,deadline);
    done(0);
}
//нарастить номер счёта
void Settings::take_new_number(int number)
{
    data[8] = QString::number(number+1);
}

//добавить новый
void Settings::take_new_data(int row, QString new_data)
{
    switch(row)
    {
      case 0:
        target.append(new_data);
        break;

      case 1:
        payment_order.append(new_data);
        break;

      case 2:
        warranty.append(new_data);
        break;

      case 3:
        deadline.append(new_data);
        break;


    }
}

void Settings::take_new_data(QStringList new_data, QStringList new_target, QStringList new_order, QStringList new_warranty, QStringList new_deadline)
{
    data = new_data;
    target = new_target;
    payment_order = new_order;
    warranty = new_warranty;
    deadline = new_deadline;
    save();
}

void SettingsDialog::clear()
{
    for(int i = 0; i < 11; i++)
        l_edit[i]->clear();
    target_view->clear();
    order_view->clear();
    warranty_view->clear();
    deadline_view->clear();
}
void SettingsDialog::delete_list_item()
{
    if(target_view->selectedItems().size()!=0)
    {
        QList< QListWidgetItem* > items = target_view->selectedItems();
                    foreach( QListWidgetItem* item, items )
                    {
                        int row = target_view->row( item );
                        target_view->takeItem( row );
                        delete item;
                    }
        return;
    }
    if(order_view->selectedItems().size()!=0)
    {
        QList< QListWidgetItem* > items = order_view->selectedItems();
                    foreach( QListWidgetItem* item, items )
                    {
                        int row = order_view->row( item );
                        order_view->takeItem( row );
                        delete item;
                    }
                    return;
    }
    if(warranty_view->selectedItems().size()!=0)
    {
        QList< QListWidgetItem* > items = warranty_view->selectedItems();
                    foreach( QListWidgetItem* item, items )
                    {
                        int row = warranty_view->row( item );
                        warranty_view->takeItem( row );
                        delete item;
                    }
                    return;
    }
    if(deadline_view->selectedItems().size()!=0)
    {
        QList< QListWidgetItem* > items = deadline_view->selectedItems();
                    foreach( QListWidgetItem* item, items )
                    {
                        int row = deadline_view->row( item );
                        deadline_view->takeItem( row );
                        delete item;
                    }
    }
}

void SettingsDialog::load(Settings *data)
{
    clear();

    for(int i = 0; i < 11; i++)
        l_edit[i]->setText(data->data.at(i));

    target_view->addItems(data->target);
    order_view->addItems(data->payment_order);
    warranty_view->addItems(data->warranty);
    deadline_view->addItems(data->deadline);




    exec();
}
void SettingsDialog::edit_list_view(QListWidgetItem *item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    target_view->editItem(item);
}
void SettingsDialog::edit_order_view(QListWidgetItem *item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    order_view->editItem(item);
}
void SettingsDialog::edit_warranty_view(QListWidgetItem *item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    warranty_view->editItem(item);
}
void SettingsDialog::edit_deadline_view(QListWidgetItem *item)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    deadline_view->editItem(item);
}
