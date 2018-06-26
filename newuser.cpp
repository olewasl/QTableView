    #include <QDialog>
    #include <QLabel>
    #include <QLineEdit>
    #include <QPushButton>
    #include <QVBoxLayout>
    #include <QHBoxLayout>
    #include <QMessageBox>
    #include <newuser.h>
    #include <modelviewdemowidget.h>


    NewUser::NewUser(QWidget *parent) :
        QDialog(parent)
    {
        label11=new QLabel(tr("&Number     "));
        lineNumb=new QLineEdit;
        label11->setBuddy(lineNumb);

        label1=new QLabel(tr("&Name        "));
        lineName=new QLineEdit;
        label1->setBuddy(lineName);

        label2=new QLabel(tr("&SurName   "));
        lineSurname=new QLineEdit;
        label2->setBuddy(lineSurname);

        label3=new QLabel(tr("&Patronimyc"));
        linePatronymic=new QLineEdit;
        label3->setBuddy(linePatronymic);

        label4=new QLabel(tr("&Position     "));
        linePosition=new QLineEdit;
        label4->setBuddy(linePosition);

        label5=new QLabel(tr("&Hours        "));
        lineHours=new QLineEdit;
        label5->setBuddy(lineHours);

        label6=new QLabel(tr("&HrPay        "));
        lineHrpay=new QLineEdit;
        label6->setBuddy(lineHrpay);

        label7=new QLabel(tr("&Premy        "));
        linePremy=new QLineEdit;
        label7->setBuddy(linePremy);

        label8=new QLabel(tr("&Experince  "));
        lineExperience=new QLineEdit;
        label8->setBuddy(lineExperience);

        label9=new QLabel(tr("&Salary        "));
        lineSalary=new QLineEdit;
        label9->setBuddy(lineSalary);

        QPushButton *okButton=new QPushButton(tr("&OK"));
        QPushButton *cancelButton=new QPushButton(tr("&Cancel"));

        QHBoxLayout *hboxLayout11=new QHBoxLayout;
        QHBoxLayout *hboxLayout1=new QHBoxLayout;
        QHBoxLayout *hboxLayout2=new QHBoxLayout;
        QHBoxLayout *hboxLayout3=new QHBoxLayout;
        QHBoxLayout *hboxLayout4=new QHBoxLayout;
        QHBoxLayout *hboxLayout5=new QHBoxLayout;
        QHBoxLayout *hboxLayout6=new QHBoxLayout;
        QHBoxLayout *hboxLayout7=new QHBoxLayout;
        QHBoxLayout *hboxLayout8=new QHBoxLayout;
        QHBoxLayout *hboxLayout9=new QHBoxLayout;
        QHBoxLayout *hboxLayout10=new QHBoxLayout;

        hboxLayout11->addWidget(label11);
        hboxLayout11->addWidget(lineNumb);

        hboxLayout1->addWidget(label1);
        hboxLayout1->addWidget(lineName);

        hboxLayout2->addWidget(label2);
        hboxLayout2->addWidget(lineSurname);

        hboxLayout3->addWidget(label3);
        hboxLayout3->addWidget(linePatronymic);

        hboxLayout4->addWidget(label4);
        hboxLayout4->addWidget(linePosition);

        hboxLayout5->addWidget(label5);
        hboxLayout5->addWidget(lineHours);

        hboxLayout6->addWidget(label6);
        hboxLayout6->addWidget(lineHrpay);

        hboxLayout7->addWidget(label7);
        hboxLayout7->addWidget(linePremy);

        hboxLayout8->addWidget(label8);
        hboxLayout8->addWidget(lineExperience);

        hboxLayout9->addWidget(label9);
        hboxLayout9->addWidget(lineSalary);

        hboxLayout10->addWidget(okButton);
        hboxLayout10->addWidget(cancelButton);

        QVBoxLayout *mainLayout=new QVBoxLayout;
        mainLayout->addLayout(hboxLayout11);
        mainLayout->addLayout(hboxLayout1);
        mainLayout->addLayout(hboxLayout2);
        mainLayout->addLayout(hboxLayout3);
        mainLayout->addLayout(hboxLayout4);
        mainLayout->addLayout(hboxLayout5);
        mainLayout->addLayout(hboxLayout6);
        mainLayout->addLayout(hboxLayout7);
        mainLayout->addLayout(hboxLayout8);
        mainLayout->addLayout(hboxLayout9);
        mainLayout->addLayout(hboxLayout10);


        setLayout(mainLayout);
        setWindowTitle("New User");

       lineName->text();
       connect(okButton,SIGNAL(clicked()),this,SLOT(slotNuButton()));
       connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    }

    NewUser::~NewUser()
    {

    }

    void NewUser::slotNuButton()
    {

      emit nuButton();
    }


   QString NewUser::getName()
    {

       QString lName;
       lName=lineName->text();
        return lName;
    }

   QString NewUser::getSurname()
   {
       QString lSurName;
       lSurName=lineSurname->text();
       return lSurName;
   }

   QString NewUser::getHours()
   {
       QString lHours;
       lHours=lineHours->text();
       return lHours;
   }
   QString NewUser::getExperience()
   {
       QString lExperience;
       lExperience=lineExperience->text();
       return lExperience;
   }
   QString NewUser::getSalary()
   {
       QString lSalary;
       lSalary=lineSalary->text();
       return lSalary;
   }
   QString NewUser::getPremy()
   {
       QString lPremy;
       lPremy=linePremy->text();
       return lPremy;
   }

   QString NewUser::getHrPay()
   {
     QString lHrPay;
     lHrPay=lineHrpay->text();
      return lHrPay;
   }

   void NewUser::setHours(QString Var4)
   {
       lineHours->setText(Var4);
   }

   void NewUser::setExperience(QString Exper)
   {
       lineExperience->setText(Exper);
   }

   void NewUser::setHrPay(QString hPay)
   {
       lineHrpay->setText(hPay);
   }
   void NewUser::setSalary(QString hSal)
   {
       lineSalary->setText(hSal);
   }

   void NewUser::setPremy(QString Pry)
   {
       linePremy->setText(Pry);
   }
/*    void NewUser::addUser()
    {

        QMessageBox msgBox1;
        msgBox1.setText("JK");
        msgBox1.exec();

        nUserDialog=new NewUser(this);
        nUserDialog->show();
        nUserDialog->raise();
        nUserDialog->activateWindow();


    }   */



    //void NewUser::okClicked()
    //{

      //  QString textName=lineName->text();
       // QString Name=textName;
     // QString textName1=lineName->setText("Error");
     //   QString s_surname=lineSurname->text();
     //    QMessageBox msgBox;
     //   //msgBox.setText("Nice weekend");
     //   msgBox.setText("Name");
     //   msgBox.exec();




      //  lineSurname->setText(get_Name());

      /*  worker wk;
        wk.set_name(Name);
        wk.set_surname(s_surname);
        wk.show_name();

        lineSurname->setText(wk.get_name());

    */


    /*    int Expc=lineExperience->text().toDouble();  //Перевод из строки в число
        int Expc1=lineHrpay->text().toDouble();
        Expc1=Expc1+Expc;

    */

     /*   QString val1=QString::number(Expc1); //Перевод из числа в строку
        QMessageBox msgBox1;
        msgBox1.setText(val1);
        msgBox1.exec();



    }    */







