#include "invoice.h"
#include <QtWidgets>
#include "settings.h"
#include "kontragentstablemodel.h"
#include "standardtreemodel.h"
#include "spinboxdelegate.h"
#include "taller.h"


InvoiceDialog::InvoiceDialog()
{
    // создание виджетов
    e_number = new QSpinBox;
    e_number->setMaximumWidth(50);
    e_number->setRange(1,9999);

    e_date = new QDateEdit;
    c_customer = new QComboBox;
    c_customer->setMinimumWidth(600);


    for(int i = 0; i < 7; i++)
    {
        l_header[i] = new QLabel;
        l_customer[i] = new QLabel;
    }


    e_name = new QLineEdit;
    e_name->setPlaceholderText("ФИО");
    e_post = new QLineEdit;
    e_post->setPlaceholderText("должность");

    e_c_number = new QLineEdit;
    e_c_number->setPlaceholderText("номер договора");
    e_c_date = new QDateEdit;

    e_vac = new QLineEdit;
    e_tax = new QLineEdit;

    out_table_view = new QTableView;

    e_target = new QLineEdit;
    e_order = new QLineEdit;
    e_warranty = new QLineEdit;
    e_deadline = new QLineEdit;

    pb_save = new QPushButton("Сохранить");
    pb_cancel = new QPushButton("Отмена");
    pb_print = new QPushButton("Печать");
    pb_save_pdf = new QPushButton("PDF");

    QLabel *l_number = new QLabel("Счёт №:");
    QLabel *l_date = new QLabel("от:");
    QLabel *l_person = new QLabel("В лице:");
    s_person = new QComboBox;
    g_contract = new QGroupBox;
    g_contract->setTitle("Договор:");
    g_contract->setCheckable(true);
    QLabel *l_customer_choose = new QLabel("Заказчик:");
    QLabel *l_header_hand = new QLabel("<u>Исполнитель и его адрес:</u>");
    QLabel *l_header_customer = new QLabel("<u>Заказчик и его адрес:</u>");
    QLabel *l_vac = new QLabel("НДС");
    QLabel *l_tax = new QLabel("Основание");
    QLabel *l_group = new QLabel("Группа");
    s_group = new QComboBox;
    QLabel *l_target = new QLabel("Цель приобретения");
    QLabel *l_order = new QLabel("Порядок оплаты");
    QLabel *l_warranty = new QLabel("Гарантийный срок");
    QLabel *l_deadline = new QLabel("Срок выполнения");
    l_out_price = new QLabel;
    l_propis = new QLabel;
    QLabel *l_summ = new QLabel("<u>Итого:</u>");

    regEx = new QLineEdit;
    regEx->setPlaceholderText("фильтр услуг");
    e_new_service = new QLineEdit;
    e_new_service->setPlaceholderText("новая улуга");
    e_new_price = new QLineEdit;
    e_new_price->setPlaceholderText("цена");
    e_new_price->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.,][0-9]{2}")));
    pb_add_new_service = new QPushButton("+");
    pb_add_new_service->setEnabled(false);
    group_tab_view = new QTableView;
    group_tab_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    services_model = new QStandardItemModel;
    out_table_view->setModel(services_model);


    s_target = new QComboBox;
    s_order = new QComboBox;
    s_warranty = new QComboBox;
    s_deadline = new QComboBox;

    group_proxy_model =  new QSortFilterProxyModel;
    intDelegate = new SpinBoxDelegate;
    doubleDelegate = new DoubleSpinBoxDelegate;

    out_table_view->setItemDelegateForColumn(1,intDelegate);
    out_table_view->setItemDelegateForColumn(2,doubleDelegate);

    QVBoxLayout *megatop_layout = new QVBoxLayout;
    QHBoxLayout *hor_header_layout = new QHBoxLayout;
    QHBoxLayout *hor_header_customer_hand = new QHBoxLayout;
    QVBoxLayout *v_left_customer_hand = new QVBoxLayout;
    QHBoxLayout *h_left_customer_hand = new QHBoxLayout;
    QVBoxLayout *v_right_customer_hand = new QVBoxLayout;
    QHBoxLayout *h_right_customer_hand = new QHBoxLayout;
    QHBoxLayout *hor_second_layout = new QHBoxLayout;
    QVBoxLayout *v_left_person_contract = new QVBoxLayout;
    QVBoxLayout *v_right_group_price = new QVBoxLayout;
    QHBoxLayout *h_person_one = new QHBoxLayout;
    QHBoxLayout *h_person_two = new QHBoxLayout;
    QHBoxLayout *h_person_three = new QHBoxLayout;
    QHBoxLayout *h_person_four = new QHBoxLayout;
    QHBoxLayout *group_box_layout = new QHBoxLayout;
    QHBoxLayout *h_group_one = new QHBoxLayout;
    QHBoxLayout *h_group_two = new QHBoxLayout;
    QHBoxLayout *h_price_line = new QHBoxLayout;
    QHBoxLayout *h_target = new QHBoxLayout;
    QHBoxLayout *h_order = new QHBoxLayout;
    QHBoxLayout *h_warranty = new QHBoxLayout;
    QHBoxLayout *h_deadline = new QHBoxLayout;
    QHBoxLayout *h_buttons = new QHBoxLayout;

    //Отлавливание нажатия кнопки delete
    QShortcut *shortcut1 = new QShortcut(QKeySequence( Qt::Key_Delete ),out_table_view);



    hor_header_layout->addWidget(l_number);
    hor_header_layout->addWidget(e_number);
    hor_header_layout->addWidget(l_date);
    hor_header_layout->addWidget(e_date);
    hor_header_layout->addStretch(1);
    hor_header_layout->addWidget(l_customer_choose);
    hor_header_layout->addWidget(c_customer);

    v_left_customer_hand->addWidget(l_header_hand);
    v_right_customer_hand->addWidget(l_header_customer);

    for(int i = 0; i < 4; i++)
    {
        v_left_customer_hand->addWidget(l_header[i]);
        v_right_customer_hand->addWidget(l_customer[i]);
    }
    for(int i = 4; i < 7; i++)
    {
        h_left_customer_hand->addWidget(l_header[i]);
        h_right_customer_hand->addWidget(l_customer[i]);
    }
    v_left_customer_hand->addLayout(h_left_customer_hand);
    v_right_customer_hand->addLayout(h_right_customer_hand);

    group_box_layout->addWidget(e_c_number);
    group_box_layout->addWidget(e_c_date);
    g_contract->setLayout(group_box_layout);

    h_person_one->addWidget(l_person);
    h_person_one->addWidget(s_person);
    h_person_one->addStretch(1);


    h_person_two->addWidget(e_name);
    h_person_two->addWidget(e_post);

    h_person_three->addWidget(l_vac);
    h_person_three->addWidget(e_vac);

    h_person_four->addWidget(l_tax);
    h_person_four->addWidget(e_tax);


    v_left_person_contract->addLayout(h_person_one);
    v_left_person_contract->addLayout(h_person_two);
    v_left_person_contract->addWidget(g_contract);
    v_left_person_contract->addLayout(h_person_three);
    v_left_person_contract->addLayout(h_person_four);
    v_left_person_contract->addStretch(1);



    h_group_one->addWidget(l_group);
    h_group_one->addWidget(s_group);
    h_group_one->addStretch(1);

    h_group_two->addWidget(e_new_service);
    h_group_two->addWidget(e_new_price);
    e_new_price->setMaximumWidth(70);
    h_group_two->addWidget(pb_add_new_service);
    pb_add_new_service->setMaximumWidth(50);

    v_right_group_price->addLayout(h_group_one);
    v_right_group_price->addWidget(regEx);
    v_right_group_price->addLayout(h_group_two);
    v_right_group_price->addWidget(group_tab_view);
    v_right_group_price->addStretch(1);
    group_tab_view->setMaximumHeight(92);

    h_price_line->addWidget(l_summ);
    h_price_line->addWidget(l_out_price);
    h_price_line->addWidget(l_propis);
    h_price_line->addStretch(1);



    h_target->addWidget(l_target);
    h_target->addWidget(s_target);
    s_target->setMaximumWidth(250);
    h_target->addWidget(e_target);

    h_order->addWidget(l_order);
    h_order->addWidget(s_order);
    s_order->setMaximumWidth(250);
    h_order->addWidget(e_order);

    h_warranty->addWidget(l_warranty);
    h_warranty->addWidget(s_warranty);
    s_warranty->setMaximumWidth(250);
    h_warranty->addWidget(e_warranty);

    h_deadline->addWidget(l_deadline);
    h_deadline->addWidget(s_deadline);
    s_deadline->setMaximumWidth(250);
    h_deadline->addWidget(e_deadline);

    h_buttons->addWidget(pb_save);
    h_buttons->addWidget(pb_cancel);
    h_buttons->addWidget(pb_print);
    h_buttons->addWidget(pb_save_pdf);


    //исполнитель и заказчик
    hor_header_customer_hand->addLayout(v_left_customer_hand);
    hor_header_customer_hand->addLayout(v_right_customer_hand);

    //лицо, договор, преискурант
    hor_second_layout->addLayout(v_left_person_contract);
    hor_second_layout->addLayout(v_right_group_price);

    megatop_layout->addLayout(hor_header_layout);
    megatop_layout->addLayout(hor_header_customer_hand);
    megatop_layout->addLayout(hor_second_layout);

    megatop_layout->addWidget(out_table_view);
    megatop_layout->setStretch(3,1);
    megatop_layout->addLayout(h_price_line);

    megatop_layout->addLayout(h_target);
    megatop_layout->addLayout(h_order);
    megatop_layout->addLayout(h_warranty);
    megatop_layout->addLayout(h_deadline);

    megatop_layout->addLayout(h_buttons);



    setLayout(megatop_layout);



    connect(s_target,SIGNAL(activated(QString)),e_target,SLOT(setText(QString)));
    connect(s_order,SIGNAL(activated(QString)),e_order,SLOT(setText(QString)));
    connect(s_warranty,SIGNAL(activated(QString)),e_warranty,SLOT(setText(QString)));
    connect(s_deadline,SIGNAL(activated(QString)),e_deadline,SLOT(setText(QString)));

    connect(c_customer,SIGNAL(currentIndexChanged(int)),this,SIGNAL(send_kontragent_row(int)));
    connect(s_group,SIGNAL(activated(int)),this,SIGNAL(send_preiskurant_group(int)));
    connect(s_person,SIGNAL(activated(int)),this,SLOT(set_persons(int)));
    connect(regEx,SIGNAL(textEdited(QString)),this,SLOT(filterRegExpChanged()));

    connect(e_new_service,SIGNAL(textEdited(QString)),this,SLOT(new_service_edited()));
    connect(e_new_price,SIGNAL(textEdited(QString)),this,SLOT(new_service_edited()));
    connect(pb_add_new_service,SIGNAL(clicked(bool)),this,SLOT(add_new_service()));

    connect(group_tab_view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(add_service_from_group(QModelIndex)));
    connect(out_table_view->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(save_edit_data_in_out_tab(QModelIndex)));


    connect(shortcut1,SIGNAL(activated()),this,SLOT(delete_out_row()));

    connect(pb_save,SIGNAL(clicked(bool)),this,SLOT(pb_save_clicked()));


}
//кнопка сохранить
void InvoiceDialog::pb_save_clicked()
{
    //1 - проверяем на наличие новых нижних полей

    if( s_target->findText(e_target->text()) == -1 )
        find_new_text(0,e_target->text());
    if( s_order->findText(e_order->text()) == -1 )
        find_new_text(1,e_order->text());
    if( s_warranty->findText(e_warranty->text()) == -1 )
        find_new_text(2,e_warranty->text());
    if( s_deadline->findText(e_deadline->text()) == -1 )
        find_new_text(3,e_deadline->text());

    //2 - обновить счёт в настройках

    send_last_number(e_number->value());

    //3 - проверка на наличие новых данных лица

    bool insert = false;
    for(int i = 0; i < s_person->count(); i++)
        if(s_person->itemText(i).indexOf(e_name->text()) !=-1)
        {
            insert = true;
            break;
        }
    if(!insert)
        send_new_person(c_customer->currentIndex(),e_name->text(),e_post->text());


    //4 - сохранение данных в модель

    //5 - закрытие
}

//Удаление выбранных строк в out_table
void InvoiceDialog::delete_out_row()
{
    //проверка если есть фокус
    if (out_table_view->hasFocus())
    {
        QModelIndexList indexes = out_table_view->selectionModel()->selection().indexes();
        for (int i = 0; i < indexes.count(); ++i)
        {
            QModelIndex index = indexes.at(i);
            services_model->removeRow(index.row());
        }
        recalculate();
        out_table_view->resizeRowsToContents();
        out_table_view->resizeColumnsToContents();
    }


}

//если изменяется количество штук либо цена
void InvoiceDialog::save_edit_data_in_out_tab(QModelIndex current_index)
{
    qDebug() << current_index.data();
    services_model->item(current_index.row(),3)->setText(
                QString::number(services_model->index(current_index.row(),2).data().toDouble()*services_model->index(current_index.row(),1).data().toInt(),'f',2));
    recalculate();
    out_table_view->resizeRowsToContents();
    out_table_view->resizeColumnsToContents();
}

//добавление услуги по двойному клику
void InvoiceDialog::add_service_from_group(QModelIndex current_index)
{
    QList<QStandardItem*> items;
    int row = current_index.row();
    QStandardItem *item = new QStandardItem(group_proxy_model->index(row,0).data().toString());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
    items << item;
    items << new QStandardItem("1");
    //подстановка выбранной цены из первого либо второго столбца
    if(current_index.column()== 2)
    {

        items << new QStandardItem(QString::number( group_proxy_model->index(row,2).data().toDouble(), 'f', 2 ));
        QStandardItem *item2 = new QStandardItem(QString::number( group_proxy_model->index(row,2).data().toDouble(), 'f', 2 ));
        item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
        items << item2;
    }
    else
    {

        items << new QStandardItem(QString::number( group_proxy_model->index(row,1).data().toDouble(), 'f', 2 ));
        QStandardItem *item2 = new QStandardItem(QString::number( group_proxy_model->index(row,1).data().toDouble(), 'f', 2 ));
        item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled);
        items << item2;
    }
    services_model->appendRow(items);
    out_table_view->resizeColumnsToContents();
    out_table_view->resizeRowsToContents();

    recalculate();
}
//перерасчёт суммы
void InvoiceDialog::recalculate()
{
    double summ = 0.0;
    for(int i = 0; i < services_model->rowCount(); i++)
        summ += services_model->index(i,3).data().toDouble();


    l_out_price->setText(QString::number(summ,'f',2));
    recalculate_propis();
}
//перерасчёт суммы прописью
void InvoiceDialog::recalculate_propis()
{
    l_propis->setText(taller(l_out_price->text().toDouble()));
}
//добавляем новую услугу в обе таблицы
void InvoiceDialog::add_new_service()
{
    send_new_service(s_group->currentIndex(),QStringList() << e_new_service->text() << e_new_price->text());
    send_preiskurant_group(s_group->currentIndex());

    QList<QStandardItem*> items;
    items << new QStandardItem(e_new_service->text());
    items << new QStandardItem("1");
    items << new QStandardItem(QString::number( e_new_price->text().toDouble(), 'f', 2 ));
    items << new QStandardItem(QString::number( e_new_price->text().toDouble(), 'f', 2 ));

    services_model->appendRow(items);

    out_table_view->resizeRowsToContents();
    out_table_view->resizeColumnsToContents();

    e_new_price->clear();
    e_new_service->clear();

    recalculate();
}

void InvoiceDialog::new_service_edited()
{
    e_new_price->setText(e_new_price->text().replace(",","."));
    if((e_new_price->text().size()!=0)&&(e_new_service->text().size()!=0))
        pb_add_new_service->setEnabled(true);
    else
        pb_add_new_service->setEnabled(false);
}

void InvoiceDialog::set_persons(int row)
{
    e_name->setText(person_name.at(row));
    e_post->setText(person_post.at(row));
}

void InvoiceDialog::take_group_model(QStandardItemModel *group_model)
{
    //delete group_tab_view->model();
    group_proxy_model->setSourceModel(group_model);

    group_tab_view->setModel(group_proxy_model);
    group_tab_view->resizeColumnsToContents();
    group_tab_view->resizeRowsToContents();
}

//заполнение контрагента
void InvoiceDialog::set_kontragents(QStringList data)
{
    //qDebug() << data;

    //l_customer[0];
    l_customer[0]->setText(data.at(0));
    l_customer[1]->setText(data.at(1));
    l_customer[2]->setText("УНП "+data.at(2));
    l_customer[3]->setText("р/с "+data.at(3));
    l_customer[4]->setText("в "+data.at(4));
    l_customer[5]->setText(data.at(5));
    l_customer[6]->setText("код "+data.at(6));
    if(data.at(7) == "")
    {
        g_contract->setChecked(false);
    }
    else
    {
        g_contract->setChecked(true);
        e_c_number->setText(data.at(7));
        e_c_date->setDate(QDate::fromString(data.at(8),"dd.MM.yyyy"));
    }
    person_name.clear();
    person_post.clear();
    s_person->clear();
    for( int i = 9; i < data.count(); i+=2)
    {
        person_name.append(data.at(i));
        person_post.append(data.at(i+1));
        s_person->addItem(data.at(i) + " - " + data.at(i+1));

    }
    if(person_name.count() == 0)
    {
        e_name->clear();
        e_post->clear();
    }
    else
    {
        set_persons(0);
    }

}
// запуск окна
void InvoiceDialog::new_check(Settings *setting, KontragentsTableModel *kontragents, StandardTreeModel *prices)
{
    qDebug() << setting->data;
    clear();

    l_header[0]->setText(setting->data.at(0));
    l_header[1]->setText(setting->data.at(1));
    l_header[2]->setText("УНП "+setting->data.at(2));
    l_header[3]->setText("р/с "+setting->data.at(3));
    l_header[4]->setText("в "+setting->data.at(4));
    l_header[5]->setText(setting->data.at(5));
    l_header[6]->setText("код "+setting->data.at(6));

    QString value = setting->data.at(8);


    e_number->setValue(value.toInt());
    e_date->setDate(QDate::currentDate());
    e_vac->setText(setting->data.at(9));
    e_tax->setText(setting->data.at(10));


    s_target->addItems(setting->target);
    s_order->addItems(setting->payment_order);
    s_warranty->addItems(setting->warranty);
    s_deadline->addItems(setting->deadline);

    e_target->setText(s_target->itemText(0));
    e_order->setText(s_order->itemText(0));
    e_warranty->setText(s_warranty->itemText(0));
    e_deadline->setText(s_deadline->itemText(0));


    c_customer->setModel(kontragents);
    c_customer->setModelColumn(0);

    s_group->setModel(prices);
    s_group->setModelColumn(0);





    l_propis->setText(taller(0));

    exec();
}
//фильтр подгруппы
void InvoiceDialog::filterRegExpChanged()
{

    QRegExp regExp(regEx->text(), Qt::CaseInsensitive, QRegExp::FixedString);

    group_proxy_model->setFilterKeyColumn(0);
    group_proxy_model->setFilterRegExp(regExp);

    group_tab_view->resizeColumnsToContents();
    group_tab_view->resizeRowsToContents();

}
void InvoiceDialog::clear()
{
    for(int i = 0; i < 7; i++)
    {
        l_header[i]->text().clear();
        l_customer[i]->text().clear();
    }

    services_model->clear();
    services_model->setHorizontalHeaderLabels(QStringList() << "Наименование" << "Кол-во" << "Цена" << "Сумма");

    //e_number->

    e_vac->text().clear();
    e_tax->text().clear();


    s_target->clear();
    s_order->clear();
    s_warranty->clear();
    s_deadline->clear();

    e_target->text().clear();
    e_order->text().clear();
    e_warranty->text().clear();
    e_deadline->text().clear();





}

