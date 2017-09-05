#ifndef INVOICE_H
#define INVOICE_H
#include <QDialog>
#include <QtWidgets>
#include <QStyledItemDelegate>


class Settings;
class KontragentsTableModel;
class StandardTreeModel;
class SpinBoxDelegate;
class DoubleSpinBoxDelegate;

class InvoiceDialog : public QDialog
{
Q_OBJECT
public:
    InvoiceDialog();
    void set_currency(double current_currency) { currency = current_currency; }
    void new_check(Settings *setting, KontragentsTableModel *kontragents, StandardTreeModel *prices);
private:
    double currency;
    QSpinBox *e_number;
    QDateEdit *e_date;
    QComboBox *c_customer;

    QLabel *l_header[7];
    QLabel *l_customer[7];

    QLineEdit *e_name;
    QLineEdit *e_post;

    QLineEdit *e_c_number;
    QDateEdit *e_c_date;

    QLineEdit *e_vac;
    QLineEdit *e_tax;

    QTableView *out_table_view;
    QTableView *group_tab_view;

    QLineEdit *e_target;
    QLineEdit *e_order;
    QLineEdit *e_warranty;
    QLineEdit *e_deadline;

    QLineEdit *e_new_price;
    QLineEdit *e_new_service;

    QPushButton *pb_add_new_service;

    QLineEdit *regEx;

    QLabel *l_propis;
    QLabel *l_out_price;

    QPushButton *pb_save;
    QPushButton *pb_cancel;
    QPushButton *pb_print;
    QPushButton *pb_save_pdf;

    QComboBox *s_target;
    QComboBox *s_order;
    QComboBox *s_warranty;
    QComboBox *s_deadline;

    QGroupBox *g_contract;

    void clear();

    QStringList person_name;
    QStringList person_post;
    QComboBox *s_person;
    QComboBox *s_group;
    QSortFilterProxyModel *group_proxy_model;

    QStandardItemModel *services_model;
    SpinBoxDelegate *intDelegate;
    DoubleSpinBoxDelegate *doubleDelegate;

    void recalculate();
    void recalculate_propis();


private slots:
    void set_kontragents(QStringList data);
    void set_persons(int row);
    void take_group_model(QStandardItemModel *group_model);
    void filterRegExpChanged();
    void new_service_edited();
    void add_new_service();
    void add_service_from_group(QModelIndex current_index);
    void save_edit_data_in_out_tab(QModelIndex current_index);

    void delete_out_row();

    void pb_save_clicked();



signals:
    void send_kontragent_row(int row);
    void send_preiskurant_group(int row);
    void send_new_service(int row, QStringList new_data);
    void find_new_text(int row, QString new_text);
    void send_last_number(int number);
    void send_new_person(int row, QString name, QString post);
};

#endif // INVOICE_H
