#include "createdialog.h"
#include <QtWidgets>
#include <QDebug>
#include <QDialog>
#include <QLayout>
#include <QLabel>

KontragentDialog::KontragentDialog()
{
    QHBoxLayout *layout_cols = new QHBoxLayout;
    QVBoxLayout *layout_left = new QVBoxLayout;
    QVBoxLayout *layout_right = new QVBoxLayout;
    QVBoxLayout *layout_general = new QVBoxLayout;
    QHBoxLayout *layout_table = new QHBoxLayout;
    QVBoxLayout *layout_table_buttons = new QVBoxLayout;
    QHBoxLayout *layout_buttons = new QHBoxLayout;



    QLabel *l_name = new QLabel("Название:");
    QLabel *l_adress = new QLabel("Адрес:");
    QLabel *l_unp = new QLabel("УНП:");
    QLabel *l_okpo = new QLabel("ОКПО");
    QLabel *l_bank_account = new QLabel("Р/с:");
    QLabel *l_bank_name = new QLabel("Банк:");
    QLabel *l_bank_adress = new QLabel("Адрес банка:");
    QLabel *l_bank_code = new QLabel("Код банка:");
    QLabel *l_republic = new QLabel("Страна:");
    QLabel *l_dogovor = new QLabel("Номер договора:");
    QLabel *l_dogovor_date = new QLabel("Дата договора:");
    QLabel *l_leadership = new QLabel("Ответственные лица:");


    layout_left->addWidget(l_name);
    layout_left->addWidget(l_adress);
    layout_left->addWidget(l_unp);
    layout_left->addWidget(l_okpo);
    layout_left->addWidget(l_bank_account);
    layout_left->addWidget(l_bank_name);
    layout_left->addWidget(l_bank_adress);
    layout_left->addWidget(l_bank_code);
    layout_left->addWidget(l_republic);
    layout_left->addWidget(l_dogovor);
    layout_left->addWidget(l_dogovor_date);



    r_name = new QLineEdit;
    r_adress = new QLineEdit;
    r_unp = new QLineEdit;
    r_okpo = new QLineEdit;
    r_bank_account = new QLineEdit;
    r_bank_name = new QLineEdit;
    r_bank_adress = new QLineEdit;
    r_bank_code = new QLineEdit;
    r_republic = new QLineEdit;
    r_dogovor = new QLineEdit;
    r_dogovor_date = new QDateEdit;
    r_dogovor_date->setDisplayFormat("dd.MM.yyyy");



    layout_right->addWidget(r_name);
    layout_right->addWidget(r_adress);
    layout_right->addWidget(r_unp);
    layout_right->addWidget(r_okpo);
    layout_right->addWidget(r_bank_account);
    layout_right->addWidget(r_bank_name);
    layout_right->addWidget(r_bank_adress);
    layout_right->addWidget(r_bank_code);
    layout_right->addWidget(r_republic);
    layout_right->addWidget(r_dogovor);
    layout_right->addWidget(r_dogovor_date);

    table_leadeship = new QTableWidget(this);
    table_leadeship->setColumnCount(2);
    table_leadeship->setHorizontalHeaderLabels(QStringList() << tr("Имя") << tr("Должность"));

    layout_table->addWidget(l_leadership);
    layout_table->addWidget(table_leadeship);

    QPushButton *add_pb = new QPushButton("+");
    add_pb->setMaximumWidth(30);
    QPushButton *delete_pb = new QPushButton("-");
    delete_pb->setMaximumWidth(30);


    layout_table_buttons->addWidget(add_pb);
    layout_table_buttons->addWidget(delete_pb);

    layout_table->addLayout(layout_table_buttons);

    save = new QPushButton("Сохранить");
    cancel = new QPushButton("Отмена");

    layout_buttons->addWidget(save);
    layout_buttons->addWidget(cancel);


    layout_cols->addLayout(layout_left);
    layout_cols->addLayout(layout_right);
    layout_general->addLayout(layout_cols);
    layout_general->addLayout(layout_table);
    layout_general->addLayout(layout_buttons);


    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(r_dogovor,SIGNAL(textChanged(QString)),this,SLOT(check_dogovor(QString)));
    connect(save,SIGNAL(clicked(bool)),this,SLOT(check_save()));
    connect(add_pb,SIGNAL(clicked(bool)),this,SLOT(add_table_row()));
    connect(table_leadeship,SIGNAL(cellClicked(int,int)),this,SLOT(save_table_position(int,int)));
    connect(delete_pb,SIGNAL(clicked(bool)),this,SLOT(delete_table_row()));

    setLayout(layout_general);
}
void KontragentDialog::edit_kontragent(QStringList rowData)
{

    qDebug() << rowData;
    //clear_data();
    table_leadeship->clear();
    if(table_leadeship->rowCount()>0)
        table_leadeship->removeRow(table_leadeship->rowCount()-1);
    table_leadeship->setHorizontalHeaderLabels(QStringList() << tr("Имя") << tr("Должность"));
    row = -1;
    is_edit = true;

    r_name->setText(rowData.at(0));
    r_adress->setText(rowData.at(1));
    r_unp->setText(rowData.at(2));
    r_okpo->setText(rowData.at(3));
    r_bank_account->setText(rowData.at(4));
    r_bank_name->setText(rowData.at(5));
    r_bank_adress->setText(rowData.at(6));
    r_bank_code->setText(rowData.at(7));
    r_republic->setText(rowData.at(8));
    r_dogovor->setText(rowData.at(9));
    if(r_dogovor->text().isEmpty())
    {
        r_dogovor_date->clear();
        r_dogovor_date->setDisabled(true);
    }
    else
        r_dogovor_date->setDate(QDate::fromString(rowData.at(10),"dd.MM.yyyy"));

    if(rowData.count() > 10)
        row = 0;
    for(int i = 11; i < rowData.count(); i=i+2)
    {
        table_leadeship->setRowCount(row+1);
        QTableWidgetItem *item = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();

        item->setText(rowData.at(i)); // вставляем текст
        item2->setText(rowData.at(i+1));
        table_leadeship->setItem(row, 0, item);
        table_leadeship->setItem(row, 1, item2);
        row++;
        qDebug() << rowData.at(i);
    }

    show();
}

void KontragentDialog::clear_data()
{
    is_edit = false;
    row = -1;
    r_name->clear();
    r_name->setPlaceholderText("");
    r_adress->clear();
    r_adress->setPlaceholderText("");
    r_unp->clear();
    r_unp->setPlaceholderText("");
    r_okpo->clear();
    r_bank_account->clear();
    r_bank_account->setPlaceholderText("");
    r_bank_name->clear();
    r_bank_name->setPlaceholderText("");
    r_bank_adress->clear();
    r_bank_adress->setPlaceholderText("");
    r_bank_code->clear();
    r_bank_code->setPlaceholderText("");
    r_republic->clear();
    r_republic->setText("Беларусь");
    r_dogovor->clear();
    r_dogovor_date->setDisabled(true);

    table_leadeship->clear();
    if(table_leadeship->rowCount()>0)
        table_leadeship->removeRow(table_leadeship->rowCount()-1);
    table_leadeship->setHorizontalHeaderLabels(QStringList() << tr("Имя") << tr("Должность"));
    qDebug() << "очищено";
}

void KontragentDialog::delete_table_row()
{
    if (row != -1)
    {
        table_leadeship->removeRow(row);
    }
}

void KontragentDialog::add_table_row()
{
    if(table_leadeship->rowCount() == 0 )
    {
        table_leadeship->setRowCount(table_leadeship->rowCount()+1);
        for(int i = 0; i < 2; i++ )
        {
            table_leadeship->setItem(0, i, new QTableWidgetItem());
        }
    }
    else
    {
        bool empty_data = true;
        for(int i = 0; i < table_leadeship->rowCount(); i++)
        {
            if((table_leadeship->item(i,0)->text().isEmpty())||(table_leadeship->item(i,1)->text().isEmpty()))
                empty_data = false;
        }
        if(empty_data)
        {
            table_leadeship->setRowCount(table_leadeship->rowCount()+1);
            for(int i = 0; i < 2; i++ )
            {
                table_leadeship->setItem(table_leadeship->rowCount()-1, i, new QTableWidgetItem());
            }
        }
    }
}

void KontragentDialog::check_save()
{
    bool empty_data = false;

    if (r_name->text().isEmpty())
    {
        empty_data = true;
        r_name->setPlaceholderText("обязательное поле");
    }
    if (r_adress->text().isEmpty())
    {
        empty_data = true;
        r_adress->setPlaceholderText("обязательное поле");
    }
    if (r_unp->text().isEmpty())
    {
        empty_data = true;
        r_unp->setPlaceholderText("обязательное поле");
    }
    if (r_bank_account->text().isEmpty())
    {
        empty_data = true;
        r_bank_account->setPlaceholderText("обязательное поле");
    }
    if (r_bank_name->text().isEmpty())
    {
        empty_data = true;
        r_bank_name->setPlaceholderText("обязательное поле");
    }
    if (r_bank_adress->text().isEmpty())
    {
        empty_data = true;
        r_bank_adress->setPlaceholderText("обязательное поле");
    }
    if (r_bank_code->text().isEmpty())
    {
        empty_data = true;
        r_bank_code->setPlaceholderText("обязательное поле");
    }
    if (r_republic->text().isEmpty())
    {
        empty_data = true;
        r_republic->setText("Беларусь");
    }
    if (!empty_data)
    {

        QStringList mylist;
        mylist  << r_name->text()
                << r_adress->text()
                << r_unp->text()
                << r_okpo->text()
                << r_bank_account->text()
                << r_bank_name->text()
                << r_bank_adress->text()
                << r_bank_code->text()
                << r_republic->text();
        if (r_dogovor_date->isEnabled())
            mylist << r_dogovor->text()
                   << r_dogovor_date->date().toString("dd.MM.yyyy");
        else
            mylist << "" << "";

        for(int i = 0; i < table_leadeship->rowCount(); i++)
        {
            if((!table_leadeship->item(i,0)->text().isEmpty())&&(!table_leadeship->item(i,1)->text().isEmpty()))
                mylist << table_leadeship->item(i,0)->text() << table_leadeship->item(i,1)->text();

        }

        if (!is_edit)
            sent_new_list(mylist);
        else
            sent_edit_list(mylist);
        clear_data();
        hide();
    }
}

void KontragentDialog::check_dogovor(QString text)
{
    if (text.size() == 0)
        r_dogovor_date->setDisabled(true);
    else
        r_dogovor_date->setDisabled(false);
}

bool KontragentDialog::new_kontragent()
{

    clear_data();
    show();
    return true;
}
