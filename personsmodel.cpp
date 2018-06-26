#include "personsmodel.h"
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <modelviewdemowidget.h>
#include <QDebug>

class PersonsModel;

PersonsModel::PersonsModel(QObject *parent): QAbstractTableModel(parent)
{
}
//Возвращаем количество элементов в списке

int PersonsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
        return m_persons.count();

    // FIXME: Implement me!
}
//Возвращаем заранее заготовленное значение из перечисления enum
int PersonsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
        return LAST;

    // FIXME: Implement me!
}

QVariant PersonsModel::data(const QModelIndex &index, int role)const
{
    if(!index.isValid()||
            m_persons.count()<=index.row()||
            (role!=Qt::DisplayRole && role!=Qt::EditRole))
    {
        return QVariant();
    }

    return m_persons[index.row()][Column(index.column())];

}

bool PersonsModel::setData(const QModelIndex &index, QVariant &value, int role)
{
    if(!index.isValid() || role!=Qt::EditRole || m_persons.count() <=index.row())
    {
        return false;
    }
    m_persons[index.row()] [Column(index.column())]=value;
    emit dataChanged(index, index);
    return true;
}
//Отображение заголовка для каждого столбца и строки, принимает три параметра
//номер секции- столбца и строки, ориентацию вертикально или горизонтально
// и роль, в данном случае интересует роль для отображения
QVariant PersonsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)  //отобразить текст
    {
        return QVariant();
    }
    // FIXME: Implement me!

    if(orientation==Qt::Vertical)
    {
        return section;
    }

switch(section)
{
case NUMBER:
    return trUtf8("Номер");
case SURNAME:
    return trUtf8("Фамилия");
 case NAME:
    return trUtf8("Имя");
case PATRONYMIC:
    return trUtf8("Отчество");
case POSITION:
    return trUtf8("Должность");
case HOURS:
    return trUtf8("Часы");
case HRPAY:
    return trUtf8("Оплата в час");
case PREMY:
    return trUtf8("Премия");
case EXPERIENCE:
    return trUtf8("Опыт");
case SALARY:
    return trUtf8("Зарплата");
case DELETING:
    return trUtf8("Удалить");
}
    return QVariant();
}


Qt::ItemFlags PersonsModel::flags(const QModelIndex & index)const
{
    Qt::ItemFlags flags=QAbstractTableModel::flags(index);
    if(index.isValid())
    {
        if(index.column()==DELETING)
        {
            flags|=Qt::ItemIsEditable;
        }
    }
    return flags;
}
  void PersonsModel::appendPerson(const QString &number, const QString &surname, const QString &name, const QString &patronymic, const QString &position, const QString &hours, const QString &hrpay, const QString &premy, const QString &experience, const QString &salary)
{

    PersonsData person;
    person[NUMBER]=number;
    person[SURNAME]=surname;
    person[NAME]=name;
    person[PATRONYMIC]=patronymic;
    person[POSITION]=position;
    person[HOURS]=hours;
    person[HRPAY]=hrpay;
    person[PREMY]=premy;
    person[EXPERIENCE]=experience;
    person[SALARY]=salary;
    person[DELETING]=false;

    int row=m_persons.count();
    beginInsertRows(QModelIndex(),row,row);
    m_persons.append(person);
    endInsertRows();
}

    void PersonsModel::removeSelected(QModelIndex mInd)
    {
       int i = mInd.row();
       Persons::iterator it = m_persons.begin();   
              qDebug()<<"RemoveSelected "<<mInd.row()<<" "<<mInd;
       beginRemoveRows(QModelIndex(),i ,i);
            m_persons.erase(it);
            endRemoveRows();
             emit dataChanged(mInd, mInd);
}

//############ Слот для очистки данных ##############################################################

    void PersonsModel::clearAll_Slot()
    {
        int i = 0;
        Persons::iterator it = m_persons.begin();
        while( it != m_persons.end() )
        {
            beginRemoveRows(QModelIndex(),i ,i);
             it=m_persons.erase(it);
             endRemoveRows();
         }
    }
