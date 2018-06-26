#ifndef NEWUSER_H
#define NEWUSER_H

#include <QWidget>
#include <QDialog>
#include <modelviewdemowidget.h>
#include <QValidator>

class QLineEdit;
class QLabel;
class QPushButton;
class ModelViewDemoWidget;


class NewUser : public QDialog
{
    Q_OBJECT

public:
    NewUser(QWidget *parent = 0);
     ~NewUser();
    QString getName();
    QString getSurname();
    QString getHours();
    QString getExperience();
    QString getPremy();
    QString getSalary();
    QString getHrPay();

    void setHours(QString);
    void setExperience(QString);
    void setHrPay(QString);
    void setSalary(QString);
    void setPremy(QString);

    QLineEdit *lineNumb;
    QLineEdit *lineName;
    QLineEdit *lineSurname;
    QLineEdit *linePatronymic;
    QLineEdit *linePosition;

private slots:
     void slotNuButton();
signals:
     void nuButton();

private:
    QLabel *label11;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;
    QLabel *label10;

    QLineEdit *lineExperience;
    QLineEdit *lineHrpay;
    QLineEdit *lineHours;
    QLineEdit *lineSalary;
    QLineEdit *linePremy;


};
#endif // NEWUSER_H
