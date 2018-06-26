#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <modelviewdemowidget.h>
#include <QTableView>
#include <QHeaderView>
#include <QTableWidget>
#include <personsmodel.h>
#include <QTableWidgetItem>
#include <QMessageBox>

class ModelViewDemoWidget;
class PersonsModel;


class FindWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FindWindow(QWidget *parent = 0);
    QString getFind();

private slots:
    void findSlot();
signals:
    void findSignal();
public slots:
    void insFinders(QString, QString, QString, QString, QString, QString, QString, QString, QString, QString);
    void clearModel(); //Слот для очистки модели
private:
    QLabel *label;
    QLineEdit *find;
    QPushButton *findButton;
    QPushButton *cancelButton;
    QTableView *F_VIEW;
    PersonsModel *F_MODEL;

};

#endif // FINDWINDOW_H
