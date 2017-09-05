
#include "mainwindow.h"
#include "proxymodel.h"
#include "standardtablemodel.h"
#include "kontragentstablemodel.h"
#include "uniqueproxymodel.h"
#include "settings.h"
#include "createdialog.h"
#include "standardtreemodel.h"
#include "invoice.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QIODevice>
#include <QUrl>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle(tr("%1[*]").arg("Программа "));
    //создаём модели
    model = new StandardTableModel(this, 1);
    model2 = new StandardTableModel(this, 2);
    model3 = new StandardTableModel(this, 3);
    model4 = new StandardTableModel(this, 4);
    kontragent_model = new KontragentsTableModel(this);

    treemodel = new StandardTreeModel(this);



    //создаём проксимодели для фильтрации
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);

    //создаём виджеты
    createWidgets();
    //добавить виджеты на лайоуты
    createLayouts();

    //тест
    model->save("error.data");
    model->load("error.data");
    kontragent_model->load("kontragents.data");
    treemodel->load("preiskurant.data");
    maximumPriceSpinBox->setValue(model->get_max_price());
    minimumPriceSpinBox->setValue(model->get_min_price());
    dateCalendar->setDateRange(model->get_min_date(),model->get_max_date());
    createComboBoxModels();
    //создать сигналы
    createConnections();



    // ----------- перенести в виджеты
    //Донастройка таблицы
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setSortIndicatorShown(true);
    tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    tableView->verticalHeader()->hide();

    //tableView->setColumnHidden(0,true);

    //tableView2->setModel(model->pricemodel.at(0));
    tableView2->setColumnWidth(0,240);
    tableView2->setColumnWidth(1,60);
    tableView2->setColumnWidth(2,60);
    tableView2->setColumnWidth(3,110);
    tableView2->setColumnWidth(4,60);
    tableView2->setColumnWidth(5,90);
    tableView2->resizeRowsToContents();

    treeView->hide();

    QNetworkAccessManager *nam = new QNetworkAccessManager;
    QNetworkReply *reply = nam->get(QNetworkRequest(QUrl("http://www.nbrb.by/API/ExRates/Rates/145")));
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
    regedid->hide();





    statusBar()->showMessage("Готов");

}
void MainWindow::onFinished(){
       QIODevice *content = static_cast<QIODevice*>(QObject::sender());


       QString str = QString::fromStdString( content->readAll().toStdString());
       content->deleteLater();
       QString currency;
       for(int i = str.indexOf("Rate\":")+6; i<str.length()-1; i++ )
           currency.append(str[i]);
       invoice_dialog->set_currency(currency.toDouble());


   }


void MainWindow::createWidgets()
{
    //константы высоты и длины кнопок
    const int minHeight = 40;
    const int minWidth = 110;
    hand_settings = new Settings();


    invoice_dialog = new InvoiceDialog();
    invoice_dialog->setModal(true);
    invoice_dialog->raise();
    invoice_dialog->setWindowTitle("Новый акт");

    settings_dialog = new SettingsDialog();
    settings_dialog->setModal(true);
    settings_dialog->raise();
    settings_dialog->setWindowTitle("Настройки");

    kontragent_dialog = new KontragentDialog();
    kontragent_dialog->setModal(true);
    kontragent_dialog->setModal(true);
    kontragent_dialog->setWindowTitle("Клиенты");

    //----------Создание кнопок
    pb_scf = new QPushButton;
    pb_scf->setMinimumHeight(minHeight);
    pb_scf->setText("СЧФ");

    pb_acts = new QPushButton;
    pb_acts->setMinimumHeight(minHeight);
    pb_acts->setText("Сохранить");

    pb_ttn = new QPushButton;
    pb_ttn->setMinimumHeight(minHeight);
    pb_ttn->setText("Накладные");

    pb_clients = new QPushButton;
    pb_clients->setMinimumHeight(minHeight);
    pb_clients->setText("Клиенты");

    pb_preiskurant = new QPushButton;
    pb_preiskurant->setMinimumHeight(minHeight);
    pb_preiskurant->setText("Прейскурант");

    //создание модели представления
    tableView = new QTableView;
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(proxyModel);



    treemodel->load("preiskurant.data");

    //Группа фильтров
    filterSelectGroupBox = new QGroupBox(tr("Фильтр"));
    filterSelectGroupBox->setCheckable(true);
    filterSelectGroupBox->setChecked(false);

    minimumPriceLabel = new QLabel(tr("Мин. Цена:"));
    minimumPriceSpinBox = new QSpinBox;
    minimumPriceSpinBox->setMaximum(50000);
    minimumPriceLabel->setBuddy(minimumPriceSpinBox);
    //minimumPriceSpinBox->setRange(MinPrice, MaxPrice);
    minimumPriceSpinBox->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    maximumPriceLabel = new QLabel(tr("Макс. Цена:"));
    maximumPriceSpinBox = new QSpinBox;
    maximumPriceSpinBox->setMaximum(50000);
    maximumPriceLabel->setBuddy(maximumPriceSpinBox);
    //maximumPriceSpinBox->setRange(MinZipcode, MaxZipcode);
    maximumPriceSpinBox->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    //maximumPriceSpinBox->setValue(MaxZipcode);
    clientsGroupBox = new QGroupBox(tr("Контрагент"));
    clientsGroupBox->setCheckable(true);
    clientsGroupBox->setChecked(false);
    clientsComboBox = new QComboBox;
    dateCalendar = new QCalendarWidget;
    dateGroupBox = new QGroupBox(tr("Дата"));
    dateGroupBox->setCheckable(true);
    dateGroupBox->setChecked(false);
    dateEdit = new QDateEdit;

    //Групппа навигации
    navigations_Buttons = new QGroupBox(tr("Меню"));
    print_modelData = new QPushButton;
    print_modelData->setText("Печать");
    print_modelData->setMinimumHeight(minHeight);
    print_modelData->setMinimumWidth(minWidth);
    add_modelItem = new QPushButton;
    add_modelItem->setText("Добавить");
    add_modelItem->setMinimumHeight(minHeight);
    add_modelItem->setMinimumWidth(minWidth);
    delete_modelItem = new QPushButton;
    delete_modelItem->setText("Удалить");
    delete_modelItem->setMinimumHeight(minHeight);
    delete_modelItem->setMinimumWidth(minWidth);
    edit_modelItem = new QPushButton;
    edit_modelItem->setText("Редактировать");
    edit_modelItem->setMinimumHeight(minHeight);
    edit_modelItem->setMinimumWidth(minWidth);
    save_modelItem = new QPushButton;
    save_modelItem->setText("Сохранить в PDF");
    save_modelItem->setMinimumHeight(minHeight);
    save_modelItem->setMinimumWidth(minWidth);
    settings_modelItem = new QPushButton;
    settings_modelItem->setText("Настройки");
    settings_modelItem->setMinimumHeight(minHeight);
    settings_modelItem->setMinimumWidth(minWidth);

    tableView->setMinimumWidth(850);
    tableView->sortByColumn(0,Qt::DescendingOrder);
    filterSelectGroupBox->setMaximumWidth(700);
    //navigations_Buttons->setMaximumWidth(200);
    //тест
    //clientsComboBox->addItem("ОАО БЕЛАРУСБАНК");
    tableView2 = new QTableView;

    kontragentProxyModel = new QSortFilterProxyModel;
    kontragentProxyModel->setSourceModel(kontragent_model);

    preiskurantProxyModel = new QSortFilterProxyModel;
    preiskurantProxyModel->setSourceModel(treemodel);

    //дерево услуг
    treeView = new QTreeView;
    treeView->setAllColumnsShowFocus(true);
    //treeView->setModel(treemodel);
    treeView->setModel(preiskurantProxyModel);

    //dateCalendar->setMaximumDate(QDate::currentDate());
    dateCalendar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    regedid = new QLineEdit;




}
void MainWindow::createLayouts()
{
    QVBoxLayout *layout_top = new QVBoxLayout;
    //Горизонтальные верхние кнопки
    QHBoxLayout *layout_pb = new QHBoxLayout;
    QHBoxLayout *layout_pb_out = new QHBoxLayout;
    QHBoxLayout *layout_footer = new QHBoxLayout;
    QVBoxLayout *groupBoxLeftLayout = new QVBoxLayout;

    //кнопки
    layout_pb->addWidget(pb_scf);
    layout_pb->addWidget(pb_acts);
    layout_pb->addWidget(pb_ttn);
    layout_pb->addWidget(pb_clients);
    layout_pb->addWidget(pb_preiskurant);

    groupBoxLeftLayout->addWidget(dateGroupBox);
    //groupBoxLeftLayout->addWidget(clientsGroupBox);

    QHBoxLayout *comboBoxLayout = new QHBoxLayout;
    comboBoxLayout->addWidget(dateCalendar);
    dateGroupBox->setLayout(comboBoxLayout);


    comboBoxLayout = new QHBoxLayout;
    comboBoxLayout->addWidget(clientsComboBox);
    comboBoxLayout->addWidget(regedid);

    clientsGroupBox->setLayout(comboBoxLayout);


    QVBoxLayout *groupBoxRightLayout = new QVBoxLayout;

    groupBoxRightLayout->addWidget(clientsGroupBox);
    clientsGroupBox->setFixedHeight(100);
    clientsGroupBox->setFixedWidth(310);

    QHBoxLayout *prices = new QHBoxLayout;
    prices->addWidget(minimumPriceLabel);
    prices->addWidget(minimumPriceSpinBox);
    prices->addWidget(maximumPriceLabel);
    prices->addWidget(maximumPriceSpinBox);
    groupBoxRightLayout->addLayout(prices);

    groupBoxRightLayout->setAlignment(clientsGroupBox,Qt::AlignTop);
    groupBoxRightLayout->setAlignment(prices,Qt::AlignTop);

    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addLayout(groupBoxLeftLayout);
    groupBoxLayout->addLayout(groupBoxRightLayout);
    filterSelectGroupBox->setLayout(groupBoxLayout);


    QVBoxLayout *buttons_row_1 = new QVBoxLayout;
    buttons_row_1->addWidget(add_modelItem);
    buttons_row_1->addWidget(delete_modelItem);
    buttons_row_1->addWidget(save_modelItem);
    QVBoxLayout *buttons_row_2 = new QVBoxLayout;
    buttons_row_2->addWidget(print_modelData);
    buttons_row_2->addWidget(edit_modelItem);
    buttons_row_2->addWidget(settings_modelItem);
    QHBoxLayout *navigations_Buttons_rows = new QHBoxLayout;
    navigations_Buttons_rows->addLayout(buttons_row_1);
    navigations_Buttons_rows->addLayout(buttons_row_2);

    navigations_Buttons->setLayout(navigations_Buttons_rows);


    layout_pb_out->addWidget(tableView);
    layout_pb_out->addWidget(tableView2);
    layout_pb_out->addWidget(treeView);
    layout_pb_out->setStretch(4,1);

    layout_footer->addWidget(filterSelectGroupBox);
    layout_footer->addWidget(navigations_Buttons);


    layout_footer->setAlignment(filterSelectGroupBox,Qt::AlignLeft);
    layout_footer->setAlignment(navigations_Buttons,Qt::AlignLeft);
    layout_footer->setSpacing(1);
    layout_footer->addStretch(5);

    layout_top->addLayout(layout_pb);
    layout_top->addLayout(layout_pb_out);
    layout_top->addLayout(layout_footer);
    layout_top->setAlignment(layout_pb,Qt::AlignTop);
    layout_pb->setSpacing(2);
    layout_pb->addStretch(5);

    QWidget *widget = new QWidget;
    widget->setLayout(layout_top);
    setCentralWidget(widget);

    //dialog_createLayouts();
    //create_settings_dialog();



}
void MainWindow::createConnections()
{



    connect(pb_acts,SIGNAL(clicked(bool)),this,SLOT(push_pb_acts()));
    connect(pb_scf,SIGNAL(clicked(bool)),this,SLOT(push_pb_scf()));
    connect(pb_ttn,SIGNAL(clicked(bool)),this,SLOT(push_pb_ttn()));
    connect(pb_clients,SIGNAL(clicked(bool)),this,SLOT(push_pb_clients()));
    connect(pb_preiskurant,SIGNAL(clicked(bool)),this,SLOT(push_pb_preiskurant()));

    connect(model, SIGNAL(itemChanged(QStandardItem*)),this, SLOT(setDirty()));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),this, SLOT(setDirty()));
    connect(model, SIGNAL(modelReset()), this, SLOT(setDirty()));

    connect(filterSelectGroupBox,SIGNAL(clicked(bool)),this,SLOT(updateUi()));
    connect(clientsGroupBox, SIGNAL(toggled(bool)),this, SLOT(updateUi()));
    connect(clientsComboBox, SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));
    connect(dateGroupBox, SIGNAL(clicked(bool)),this, SLOT(updateUi()));
    connect(minimumPriceSpinBox, SIGNAL(valueChanged(int)),this, SLOT(updateUi()));
    connect(maximumPriceSpinBox, SIGNAL(valueChanged(int)),this, SLOT(updateUi()));
    connect(dateCalendar,SIGNAL(clicked(QDate)),this,SLOT(updateUi()));

    connect(tableView, SIGNAL(clicked(const QModelIndex&)),this, SLOT(change_table2(const QModelIndex&)));
   /* connect(tableView->selectionModel(),SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),this, SLOT(selectionChanged()));*/
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), tableView, SLOT(sortByColumn(int)));

    connect(add_modelItem,SIGNAL(clicked(bool)),this,SLOT(pb_add_modelItem()));
    connect(settings_modelItem,SIGNAL(clicked(bool)),this,SLOT(pb_set_settings()));

    connect(kontragent_dialog,SIGNAL(sent_new_list(QStringList)),kontragent_model,SLOT(add_new(QStringList)));
    connect(delete_modelItem,SIGNAL(clicked(bool)),this,SLOT(delete_row()));
    //connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(edit_row(QModelIndex)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),kontragent_model,SLOT(edit(QModelIndex)));
    connect(kontragent_model,SIGNAL(send_item(QStringList)),kontragent_dialog,SLOT(edit_kontragent(QStringList)));
    connect(kontragent_dialog,SIGNAL(sent_edit_list(QStringList)),kontragent_model,SLOT(take_edit(QStringList)));
    connect(regedid,SIGNAL(textEdited(QString)),this,SLOT(filterRegExpChanged()));
    //connect(treeView,SIGNAL(clicked(QModelIndex)),treemodel,SLOT(set_current_index(QModelIndex)));
    connect(treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(get_source_index(QModelIndex)));

    connect(treemodel,SIGNAL(expandall()),treeView,SLOT(expandAll()));

    connect(settings_dialog,SIGNAL(send_new_data(QStringList,QStringList,QStringList,QStringList,QStringList)),
            hand_settings,SLOT(take_new_data(QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(invoice_dialog,SIGNAL(send_kontragent_row(int)),this,SLOT(take_kontragent_row(int)));
    connect(this,SIGNAL(send_kontragent_data(QStringList)),invoice_dialog,SLOT(set_kontragents(QStringList)));
    connect(invoice_dialog,SIGNAL(send_preiskurant_group(int)),treemodel,SLOT(take_parent_row(int)));
    connect(treemodel,SIGNAL(send_child_model(QStandardItemModel*)),invoice_dialog,SLOT(take_group_model(QStandardItemModel*)));
    connect(invoice_dialog, SIGNAL(send_new_service(int,QStringList)),treemodel,SLOT(add_new_service(int,QStringList)));
    connect(invoice_dialog,SIGNAL(find_new_text(int,QString)),hand_settings,SLOT(take_new_data(int,QString)));
    connect(invoice_dialog,SIGNAL(send_last_number(int)),hand_settings,SLOT(take_new_number(int)));
    connect(invoice_dialog,SIGNAL(send_new_person(int,QString,QString)),kontragent_model,SLOT(take_new_person(int,QString,QString)));

}
void MainWindow::take_kontragent_row(int row)
{
    QStringList data;
    data << kontragent_model->index(row,0).data().toString();
    data << kontragent_model->index(row,1).data().toString();
    data << kontragent_model->index(row,2).data().toString();
    data << kontragent_model->index(row,4).data().toString();
    data << kontragent_model->index(row,5).data().toString();
    data << kontragent_model->index(row,6).data().toString();
    data << kontragent_model->index(row,7).data().toString();
    data << kontragent_model->index(row,9).data().toString();
    data << kontragent_model->index(row,10).data().toString();
    data << kontragent_model->take_leadership(kontragent_model->index(row,0).data().toString());


    send_kontragent_data(data);
}

void MainWindow::get_source_index(QModelIndex myindex)
{
    QModelIndex index;
    index = preiskurantProxyModel->mapToSource(myindex);
    treemodel->set_current_index(index);

}

void MainWindow::edit_row(QModelIndex index)
{
    if(tableView->model() == proxyModel)
    {
        qDebug() << "СЧФ: " << tableView->model()->data(index);
    }
    if(tableView->model() == kontragentProxyModel)
    {

        //kontragent_dialog->edit_kontragent(index);
        qDebug() << "Контрагенты: " <<index.row();
    }
}

void MainWindow::delete_row()
{

    QItemSelectionModel *selectionModel = new QItemSelectionModel;
    if(treeView->isHidden())
        selectionModel = tableView->selectionModel();
    else
        selectionModel = treeView->selectionModel();

    if (!selectionModel->hasSelection())
    {
        qDebug() << "удаление9(((((((((((";
        return;
    }
    QModelIndex index;
    if ((tableView->model() == proxyModel)&&(treeView->isHidden()))
    {
        index = proxyModel->mapToSource(selectionModel->currentIndex());
          qDebug() << index.row();
    }
    if ((tableView->model() == kontragentProxyModel)&&(treeView->isHidden()))
    {
        selectionModel->setModel(kontragentProxyModel);
        index = selectionModel->currentIndex();
        qDebug() << index.row();
    }





    if(!treeView->isHidden())
    {
        qDebug() << "удаление";
        selectionModel->setModel(preiskurantProxyModel);
        index = selectionModel->currentIndex();
        if (!index.isValid())
            return;
        treeView->model()->removeRow(index.row(), index.parent());

    }
    else
    {
        if (!index.isValid())
            return;
        tableView->model()->removeRow(index.row(), index.parent());
        qDebug() << "удаление2";
    }


    createComboBoxModels();

}

void MainWindow::push_pb_acts()
{
    treemodel->save("preiskurant.data");
    kontragent_model->save("kontragents.data");
}
void MainWindow::push_pb_scf()
{
    if (tableView->model() != proxyModel)
    {
        tableView->setModel(proxyModel);
        tableView->setColumnHidden(0,false);
        tableView->resizeColumnsToContents();
        tableView->verticalHeader()->hide();
    }
    if(!tableView2->isVisible())
        tableView2->setVisible(true);
    filterSelectGroupBox->setEnabled(true);
    treeView->hide();
    tableView->show();
    regedid->hide();
    clientsComboBox->show();
    filterSelectGroupBox->setChecked(false);
    clientsGroupBox->setCheckable(true);
    clientsGroupBox->setChecked(false);
    minimumPriceSpinBox->setHidden(false);
    minimumPriceLabel->setHidden(false);
    maximumPriceLabel->setHidden(false);
    maximumPriceSpinBox->setHidden(false);
    dateCalendar->setDisabled(false);
    dateGroupBox->setCheckable(true);
    dateGroupBox->setChecked(false);



}
void MainWindow::push_pb_ttn()
{
    tableView->setModel(model3);
    if(!tableView2->isVisible())
        tableView2->setVisible(true);
}
void MainWindow::push_pb_preiskurant()
{
    treeView->show();
    tableView->hide();
    if(tableView2->isVisible())
        tableView2->setVisible(false);
    treeView->setAllColumnsShowFocus(true);
    treeView->setAnimated(true);
    treeView->expandAll();
    treeView->setSortingEnabled(true);
    treeView->sortByColumn(0);
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
    treeView->resizeColumnToContents(2);

    filterSelectGroupBox->setEnabled(false);



}
void MainWindow::push_pb_clients()
{
    tableView->setModel(kontragentProxyModel);
    //tableView->setModel(kontragent_model);
    tableView->setColumnHidden(0,false);
    tableView->verticalHeader()->show();
    tableView->resizeColumnsToContents();
    if(tableView2->isVisible())
        tableView2->setVisible(false);
    filterSelectGroupBox->setEnabled(true);
    treeView->hide();
    tableView->show();
    regedid->show();
    clientsComboBox->hide();
    filterSelectGroupBox->setChecked(true);
    clientsGroupBox->setCheckable(false);
    clientsGroupBox->setChecked(true);
    minimumPriceSpinBox->setHidden(true);
    minimumPriceLabel->setHidden(true);
    maximumPriceLabel->setHidden(true);
    maximumPriceSpinBox->setHidden(true);

    dateGroupBox->setCheckable(false);
    dateCalendar->setDisabled(true);



}

void MainWindow::updateUi()
{
    if (!filterSelectGroupBox->isChecked())
    {
        qDebug() << "Галка не стоит";
        proxyModel->clearFilters();
        kontragentProxyModel->setFilterRegExp("");
        //сделать пустуую модель услуг
        return;
    }
        qDebug() << "Галка стоит";
        kontragentProxyModel->setFilterRegExp(regedid->text());
        restoreFilters();
}
void MainWindow::restoreFilters()
{
    proxyModel->setMinimumPrice(minimumPriceSpinBox->value());
    proxyModel->setMaximumPrice(maximumPriceSpinBox->value());
    proxyModel->setClient(clientsGroupBox->isChecked()
            ? clientsComboBox->currentText() : QString());
    proxyModel->setDate(dateGroupBox->isChecked()
            ? dateCalendar->selectedDate() : QDate());
    //reportFilterEffect();
}
void MainWindow::createComboBoxModels()
{
    createComboBoxModel(clientsComboBox, 3);
    //createComboBoxModel(stateComboBox, State);
}


void MainWindow::createComboBoxModel(QComboBox *comboBox, int column)
{
    delete comboBox->model();
    UniqueProxyModel *uniqueProxyModel = new UniqueProxyModel(column,this);
    uniqueProxyModel->setSourceModel(model);
    uniqueProxyModel->sort(column, Qt::AscendingOrder);
    comboBox->setModel(uniqueProxyModel);
    comboBox->setModelColumn(column);
}
//отображение таблицы услуг
void MainWindow::change_table2(const QModelIndex &index)
{
    if ((index.isValid())&&(tableView->model() == proxyModel))
    {
        //отображение модели справа
    }
}
void MainWindow::pb_add_modelItem()
{
    if ((tableView->model() == proxyModel)&&(treeView->isHidden()))
    {
        invoice_dialog->new_check(hand_settings,kontragent_model,treemodel);
        invoice_dialog->activateWindow();
    }
    if ((tableView->model() == kontragentProxyModel)&&(treeView->isHidden()))
    {
        kontragent_dialog->new_kontragent();
        kontragent_dialog->activateWindow();
    }
    if (!treeView->isHidden())
    {
        treemodel->add_row();

    }

}
void MainWindow::pb_set_settings()
{

    settings_dialog->load(hand_settings);
    //settings_dialog->activateWindow();
}
void MainWindow::filterRegExpChanged()
{



    QRegExp regExp(regedid->text(), Qt::CaseInsensitive, QRegExp::FixedString);

    if(treeView->isHidden())
    {
        kontragentProxyModel->setFilterKeyColumn(0);
        kontragentProxyModel->setFilterRegExp(regExp);
    }
    else
    {

        preiskurantProxyModel->setFilterKeyColumn(0);
        preiskurantProxyModel->setFilterRegExp(regExp);
    }


}


