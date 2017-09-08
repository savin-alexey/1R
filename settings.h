#ifndef SETTINGS_H
#define SETTINGS_H
#include <QtCore>
#include <QDialog>
#include <QtWidgets>

class Settings : public QObject
{
    Q_OBJECT

    public:

        Settings();
        ~Settings();
        bool load();
        bool save();

        QStringList data;
        QStringList target;
        QStringList payment_order;
        QStringList warranty;
        QStringList deadline;

    private:

        const qint32 MagicNumber = 0x534554;
        const qint16 FormatNumber = 100;

    private slots:

        void take_new_data(QStringList new_data, QStringList new_target, QStringList new_order, QStringList new_warranty, QStringList new_deadline);
        void take_new_data(int row, QString new_data);
        void take_new_number(int number);
};

class SettingsDialog : public QDialog
{
    Q_OBJECT

    public:

        SettingsDialog();
        void load(Settings *data);

    private:

        QLineEdit *l_edit[11];
        QListWidget *target_view;
        QListWidget *order_view;
        QListWidget *warranty_view;
        QListWidget *deadline_view;
        void clear();

     private slots:

        void edit_list_view(QListWidgetItem *item);
        void edit_order_view(QListWidgetItem *item);
        void edit_warranty_view(QListWidgetItem *item);
        void edit_deadline_view(QListWidgetItem *item);
        void delete_list_item();
        void save_clicked();

     signals:

        void send_new_data(QStringList new_data,
                           QStringList new_target,
                           QStringList new_order,
                           QStringList new_warranty,
                           QStringList new_deadline);
};
#endif // SETTINGS_H
