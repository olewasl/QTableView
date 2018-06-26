//########################  Модель #########################################
#ifndef PERSONSMODEL_H
#define PERSONSMODEL_H

#include <QAbstractTableModel>
#include <modelviewdemowidget.h>
#include <findwindow.h>


class PersonsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PersonsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, QVariant &value, int role);


    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

//#################  Добавление строк в таблицу  #####################################
   void appendPerson(const QString &del, const QString &surname, const QString &name, const QString &patronymic, const QString &position, const QString &hours, const QString &hrpay, const QString &premy, const QString &experience, const QString &salary);
public slots:
    void removeSelected(QModelIndex);
    void clearAll_Slot();

private:
//#####################  Перечисление Column для индексации столбцов таблицы
//##################### 4 столбца имя фамилия отчество выбор  ###############

    enum Column
    {
      NUMBER=0,
      SURNAME,
      NAME,
      PATRONYMIC,
      POSITION,
      HOURS,
      HRPAY,
      PREMY,
      EXPERIENCE,
      SALARY,
      DELETING,
      LAST
    };
    typedef QHash<Column, QVariant> PersonsData; //Данные модели храним в списке хэш-карт
 //ключ хэшкарты индекс столбца к нему привяжем данные произвольного типа QVariant
    typedef  QList<PersonsData> Persons;
    Persons m_persons;


};

#endif // PERSONSMODEL_H
