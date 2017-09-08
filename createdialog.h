#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H
#include <QDialog>
#include <QtWidgets>

class KontragentDialog : public QDialog
{
    Q_OBJECT

    public:

        KontragentDialog();
        bool new_kontragent();
        void clear_data();

    private:

        QTableWidget *table_leadeship;
        QPushButton *save;
        QPushButton *cancel;

        QLineEdit *r_name;
        QLineEdit *r_adress;
        QLineEdit *r_unp;
        QLineEdit *r_okpo;
        QLineEdit *r_bank_account;
        QLineEdit *r_bank_name;
        QLineEdit *r_bank_adress;
        QLineEdit *r_bank_code;
        QLineEdit *r_republic;
        QLineEdit *r_dogovor;
        QDateEdit *r_dogovor_date;

        bool is_edit = false;
        int row = -1;

    private slots:

        void check_dogovor(QString text);
        void check_save();
        void add_table_row();
        void delete_table_row();
        void save_table_position(int i, int j) {row = i; j++;}
        void edit_kontragent(QStringList rowData);

    signals:

        void sent_new_list(QStringList mydata);
        void sent_edit_list(QStringList mydata);
};
#endif // CREATEDIALOG_H
