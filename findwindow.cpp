#include "findwindow.h"
#include "modelviewdemowidget.h"


FindWindow::FindWindow(QWidget *parent) : QWidget(parent)
{

   label=new QLabel(tr("&LookingFor"));
   find=new QLineEdit();
   label->setBuddy(find);

   findButton=new QPushButton(tr("Find"));
   cancelButton=new QPushButton(tr("Cancel"));

   QHBoxLayout *hLayout=new QHBoxLayout();
   hLayout->addWidget(label);
   hLayout->addWidget(find);
   hLayout->addWidget(findButton);
   hLayout->addWidget(cancelButton);
   QVBoxLayout *vLayout=new QVBoxLayout();

   setLayout(vLayout);
   setWindowTitle("Find");
    resize(700,300);
   vLayout->addLayout(hLayout);
   F_VIEW=new QTableView;
   F_VIEW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   F_VIEW->setModel(F_MODEL=new PersonsModel);
   vLayout->addWidget(F_VIEW);
   F_VIEW->hideColumn(5);
   F_VIEW->hideColumn(6);
   F_VIEW->hideColumn(7);
   F_VIEW->hideColumn(8);
   F_VIEW->hideColumn(10);

//######################### Слоты для кнопок Cancel,Find.Второй слот для Find очистка результатов поиска для следующего поиска###########################################
   connect(cancelButton,SIGNAL(clicked()),this, SLOT(close()));
   connect(findButton, SIGNAL(clicked()), this, SLOT(clearModel()));
   connect(findButton,SIGNAL(clicked()),this,SLOT(findSlot()));
}

    void FindWindow::findSlot()
    {
        emit findSignal();
    }

    QString FindWindow::getFind()
    {
        return find->text();
    }

    void FindWindow::insFinders(QString fNumb,QString fName, QString fFamily, QString fPatronymic, QString fPosition, QString fHours, QString fHrpay, QString fPremy, QString fExperience, QString fSalary)
    {
       F_MODEL->appendPerson(fNumb, fName, fFamily,fPatronymic, fPosition, fHours, fHrpay, fPremy, fExperience, fSalary);
    }

    void FindWindow::clearModel()
    {
        F_MODEL->clearAll_Slot();
    }
