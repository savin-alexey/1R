#ifndef KONTRAGENTSTABLEMODEL_H
#define KONTRAGENTSTABLEMODEL_H

#include <QStandardItemModel>

class KontragentsTableModel : public QStandardItemModel
{
    Q_OBJECT

    public:

        explicit KontragentsTableModel(QObject *parent=0);

        QString filename() const { return m_filename; }
        void clear();
        void load(const QString &filename=QString());
        void save(const QString &filename=QString());
        QVector<QStandardItemModel*> pricemodel;
        QStringList take_leadership(QString name);

    private:

        int edit_row;
        QString key;
        void initialize();
        QString m_filename;
        QMap<QString,QStringList> leadership;

    private slots:
        void add_new(QStringList datalist);
        void edit(QModelIndex selected_index);
        void take_edit(QStringList edit_data);
        void take_new_person(int row, QString name, QString post);

    signals:

        void send_item(QStringList dataitem);
};
#endif // KONTRAGENTSTABLEMODEL_H
