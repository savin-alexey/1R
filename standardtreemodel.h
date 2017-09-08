#ifndef STANDARDTREEMODEL_H
#define STANDARDTREEMODEL_H

#include <QStandardItemModel>
#include <QDialog>

class GroupPrice_Dialog : public QDialog
{
    Q_OBJECT

    public:

        GroupPrice_Dialog();

    signals:

        void group_pb_clicked();
        void service_pb_clicked();
};

class StandardTreeModel : public QStandardItemModel
{
    Q_OBJECT

    public:

        explicit StandardTreeModel(QObject *parent=0);

        QString filename() const { return m_filename; }
        void setFilename(const QString &filename) { m_filename = filename; }
        void clear();
        void load(const QString &filename=QString());
        void save(const QString &filename=QString());

        void add_row();
        void set_current_index(QModelIndex selected_index);


    private slots:

        void add_group_row();
        void add_service_row();
        void take_parent_row(int parent_row);
        void add_new_service(int parent_row, QStringList data);

    private:

        void initialize();
        int parent_row = -2;
        int current_row = -2;
        GroupPrice_Dialog *dialog;
        QString m_filename;

    signals:

        void expandall();
        void send_child_model(QStandardItemModel *model);
};
#endif // STANDARDTREEMODEL_H
