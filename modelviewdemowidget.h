#ifndef MODELVIEWDEMOWIDGET_H
#define MODELVIEWDEMOWIDGET_H

#include <QWidget>
#include <modelviewdemowidget.h>
#include <findwindow.h>
#include <QTableView>
#include <QLineEdit>
#include <personsmodel.h>
#include <newuser.h>
#include <QAction>
#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFile>
#include <QLabel>
#include <QSortFilterProxyModel>
#include <QDataStream>
#include <QFileDialog>

class QTableView;
class PersonsModel;
class NewUser;
class FindWindow;

class ModelViewDemoWidget : public QWidget
{
    Q_OBJECT

public:
    ModelViewDemoWidget(QWidget *parent = 0);
    ~ModelViewDemoWidget();

public slots:
    void okClicked();  //Слот нажатие на кнопку ОК в форме добавление нового пользователя
    void setFind();//слот для поиска
    void delUser();
    void outDelUser();  //слот для сигнала наружу в personsmodel
    void outClearAll(); //слот для сигнала наружу в personsmodel

    void exportList();  //слот для экспорта файла в csv файл
signals:
    void FSignal();//сигнал для поиска
    void slotSignal();
    void outDelUserSignal();
private slots:
//    void onAppend();
    void addUser();
    void findData();
    void showUser();
    void openFile();
    void writeFile();
    void finding();
    void slotCustomContextMenu(QPoint);
private:
    QTableView *m_view;
    PersonsModel *m_model;
    QLineEdit *m_numbEdit;
    QLineEdit *m_surnameEdit;
    QLineEdit *m_nameEdit;
    QLineEdit *m_patronymicEdit;
    QLineEdit *m_position;
    QLineEdit *m_experience;
    QLineEdit *m_hours;
    QLineEdit *m_hrpay;
    QLineEdit *m_salary;
    QLineEdit *m_premy;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *exportAction;
    QAction *exitAction;
    QAction *newUserAction;
    QAction *findUserAction;
    QAction *delUserAction;
    QAction *clearAllAction;

    NewUser *nUserDialog;
    FindWindow *findUser;

    QSortFilterProxyModel *proxyModel;
//###########  Контекстное меню ############################################
    QMenu *menu;
    QAction *delContextUser;
    QAction *addContextUser;
    QAction *showContextUser;
};

#endif // MODELVIEWDEMOWIDGET_H
