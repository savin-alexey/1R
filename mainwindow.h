#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>
#include <QDialog>
class StandardTableModel;
class ProxyModel;
class Settings;
class KontragentsTableModel;
class KontragentDialog;
class StandardItem;
class StandardTreeModel;
class InvoiceDialog;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    QPushButton *pb_scf;
    QPushButton *pb_acts;
    QPushButton *pb_ttn;
    //QPushButton *pb_dogovor;
    QPushButton *pb_clients;
    QPushButton *pb_preiskurant;
    QTableView *tableView;
    //для правой штуки
    QTableView *tableView2;
    //для дерева услуг
    QTreeView *treeView;
    StandardTreeModel *treemodel;

    //Группа навигации
    QGroupBox *navigations_Buttons;
    QPushButton *print_modelData;
    QPushButton *add_modelItem;
    QPushButton *delete_modelItem;
    QPushButton *edit_modelItem;
    QPushButton *save_modelItem;
    QPushButton *settings_modelItem;

    //Виджеты фильтра
    QGroupBox *filterSelectGroupBox;
    QRadioButton *dontFilterOrSelectRadioButton;
    QRadioButton *filterRadioButton;
    QLabel *minimumPriceLabel;
    QSpinBox *minimumPriceSpinBox;
    QLabel *maximumPriceLabel;
    QSpinBox *maximumPriceSpinBox;
    QGroupBox *clientsGroupBox;
    QComboBox *clientsComboBox;
    QGroupBox *dateGroupBox;
    QDateEdit *dateEdit;
    QCalendarWidget *dateCalendar;

    QLineEdit *regedid;

    QNetworkAccessManager *manager;
    InvoiceDialog *invoice_dialog;
    SettingsDialog *settings_dialog;
    KontragentDialog *kontragent_dialog;
    Settings *hand_settings;

    //model - СЧФ
    StandardTableModel *model;
    //model - Акты
    StandardTableModel *model2;
    //model - ТТН
    StandardTableModel *model3;
    //model - клиенты
    StandardTableModel *model4;
    KontragentsTableModel *kontragent_model;

    ProxyModel *proxyModel;
    QSortFilterProxyModel *kontragentProxyModel;
    QSortFilterProxyModel *preiskurantProxyModel;

    void createWidgets();
    void createLayouts();
    void createConnections();
    //обновление фильтров
    void restoreFilters();
    void createComboBoxModels();
    void createComboBoxModel(QComboBox *comboBox, int column);



    //void create_settings_dialog();

    //QLineEdit *e_edit[11];


    //тест
private slots:
    //Нажатие кнопок
    void push_pb_scf();
    void push_pb_acts();
    void push_pb_ttn();
    void push_pb_clients();
    void push_pb_preiskurant();
    //при изменениии чего то, появляется звездочка, если не сохранить
    void setDirty() { setWindowModified(true); }
    //обновление фильтров
    void updateUi();
    void change_table2(const QModelIndex& index);
    void pb_add_modelItem();
    void pb_set_settings();

    void delete_row();
    void edit_row(QModelIndex index);

    //тест
    void onFinished();


    void filterRegExpChanged();
    void get_source_index(QModelIndex myindex);
    void take_kontragent_row(int row);

signals:
    void send_kontragent_data(QStringList data);

public:
    explicit MainWindow(QWidget *parent=0);



};



#endif // MAINWINDOW_H
