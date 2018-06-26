    #include "modelviewdemowidget.h"
    #include <QTableView>
    #include <QHeaderView>
    #include <QLayout>
    #include <QPushButton>
    #include <QLineEdit>
    #include <QLabel>
    #include <QGridLayout>
    #include <personsmodel.h>
    #include <QMessageBox>
    #include <newuser.h>
    #include <QDebug>
    #include <QApplication>
    #include <QMessageBox>
    #include <QStringList>
    #include <QSize>
    #include <QDebug>
    #include <iterator>

    class NewUser;
    class FindWindow;
    class PersonsModel;



    ModelViewDemoWidget::ModelViewDemoWidget(QWidget *parent)
        : QWidget(parent)
    {
        QVBoxLayout *mainLayout=new QVBoxLayout;
        setLayout(mainLayout);

        proxyModel=new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(m_model=new PersonsModel);
       // proxyModel->setFilterRegExp(QRegExp(regExp,Qt::CaseSensitive));
        proxyModel->setFilterKeyColumn(0);

        m_view=new QTableView;
        m_view->setModel(proxyModel); //подключение модели к представлению
        m_view->hideColumn(4);
        m_view->hideColumn(6);
        m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//########## Контекстное меню  #########################################################
        m_view->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(m_view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextMenu(QPoint)));

        m_view->setSortingEnabled(true);

    //***********************************************************************************************
    //************ Поля ввода внизу формы подписи к ним и кнопка
        QGridLayout *panelLayout=new QGridLayout;
        mainLayout->addLayout(panelLayout);

        this->menuBar=new QMenuBar(this);
        this->fileMenu=new QMenu(tr("&File     "));
        this->editMenu=new QMenu(tr("&Edit     "));
        this->menuBar->addMenu(this->fileMenu);
        this->menuBar->addMenu(this->editMenu);
        this->openAction=new QAction(tr("&Open file     "),this->fileMenu);
        this->saveAction=new QAction(tr("&Save file     "),this->fileMenu);
        this->exportAction=new QAction(tr("&Export to CSV     "),this->fileMenu);
        this->exitAction=new QAction(tr("&Exit"),this->fileMenu);

        this->fileMenu->addAction(openAction);
        this->fileMenu->addAction(saveAction);
        this->fileMenu->addAction(exportAction);
        this->fileMenu->addAction(exitAction);
        this->fileMenu->addActions(QList <QAction *> () <<this->openAction<< this->saveAction<< this->exportAction<<this->exitAction);

        this->newUserAction=new QAction(tr("&New user      "),this->editMenu);
        this->findUserAction=new QAction(tr("&Find      "),this->editMenu);
        this->delUserAction=new QAction(tr("&Delete user      "),this->editMenu);
        this->clearAllAction=new QAction(tr("&Clear all      "),this->editMenu);

        this->editMenu->addActions(QList <QAction *> () <<this->newUserAction<<findUserAction<<this->delUserAction<<this->clearAllAction);


        panelLayout->setMenuBar(this->menuBar);
        panelLayout->addWidget(menuBar);

        connect(openAction,SIGNAL(triggered()),this, SLOT(openFile()));

        connect(saveAction,SIGNAL(triggered()),this, SLOT(writeFile()));

        connect(exportAction,SIGNAL(triggered()),this, SLOT(exportList()));

        connect(newUserAction,SIGNAL(triggered()),this, SLOT(addUser()));

        connect(exitAction,SIGNAL(triggered()),this, SLOT(close()));

        connect(findUserAction,SIGNAL(triggered()), this, SLOT(findData()));

        connect(delUserAction, SIGNAL(triggered()), this, SLOT(outDelUser()));

        connect(clearAllAction, SIGNAL(triggered()), this, SLOT(outClearAll()));

        mainLayout->addWidget(m_view);
        setWindowTitle("Persons");

        resize(1024,600);
        connect(m_view, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(showUser()));
    }

    ModelViewDemoWidget::~ModelViewDemoWidget()
    {

    }
//##################### Слот удаление пользователя используя основное меню ##################################
    void ModelViewDemoWidget::outDelUser()
    {
        QModelIndex mnInd;
       mnInd=m_view->currentIndex();
      int ROW=m_view->currentIndex().row();
      int COLUMN=m_view->currentIndex().column();

             QModelIndex modIndex;
             modIndex=proxyModel->index(ROW,COLUMN,QModelIndex());
             QString xInd=proxyModel->data(modIndex,Qt::DisplayRole).toString();

       qDebug()<<" M_VIEW "<<" "<<"   ROW "<<ROW<<"  COLUMN "<<COLUMN ;
       qDebug()<<" M_MODEL "<<xInd;
    }

//####################### Слот нажатие на кнопку ОК в форме добавление нового пользователя  #############################
    void ModelViewDemoWidget::okClicked()
    {

          QString l_Numb;
          QString l_Name;
          QString l_SurName;
          QString l_Patronymic;
          QString l_Position;
          QString l_HrPay;
          QString l_Hours;
          QString l_Experience;
          QString l_Premy;
          QString l_Salary;

//######  Здесь нужно переписать через функцию get ###################

          l_Numb=nUserDialog->lineNumb->text();
          l_Name=nUserDialog->lineName->text();
          l_SurName=nUserDialog->lineSurname->text();
          l_Patronymic=nUserDialog->linePatronymic->text();
          l_Position=nUserDialog->linePosition->text();
          l_Hours=nUserDialog->getHours();
          l_HrPay=nUserDialog->getHrPay();
          l_Premy=nUserDialog->getPremy();
          l_Experience=nUserDialog->getExperience();
          l_Salary=nUserDialog->getSalary();


          m_numbEdit=new QLineEdit(l_Numb);
          m_nameEdit=new QLineEdit(l_Name);
          m_surnameEdit=new QLineEdit(l_SurName);
          m_patronymicEdit=new QLineEdit(l_Patronymic);
          m_position=new QLineEdit(l_Position);
          m_hours=new QLineEdit(l_Hours);
          m_experience=new QLineEdit(l_Experience);
          m_hrpay=new QLineEdit(l_HrPay);
          m_premy=new QLineEdit(l_Premy);
          m_salary=new QLineEdit(l_Salary);
//########################  Проверим поля на пустое значение  ##############
         if(!l_Name.isEmpty() && !l_SurName.isEmpty() && !l_Patronymic.isEmpty() && !l_Position.isEmpty() && !l_Hours.isEmpty() && !l_Experience.isEmpty() && !l_HrPay.isEmpty() && !l_Premy.isEmpty() && !l_Salary.isEmpty())
          {
             m_model->appendPerson(m_numbEdit->text(),m_surnameEdit->text(),m_nameEdit->text(), m_patronymicEdit->text(),m_position->text(),m_hours->text(),m_hrpay->text(),m_premy->text(),m_experience->text(),m_salary->text());
             nUserDialog->close();
          }
          else
          {
             QMessageBox boxEmpty;
              boxEmpty.setText("Enter Data to empty fields");
              boxEmpty.exec();
          }
    }

 //################ Слот для добавления нового пользователя ############################################
     void ModelViewDemoWidget::addUser()
    {

        nUserDialog=new NewUser(this);
        nUserDialog->show();
        nUserDialog->raise();
        nUserDialog->activateWindow();

//################ Сгенерировать номер нового пользователя ##############################################################

        QModelIndex nUserIndex;
        nUserIndex=m_view->currentIndex();
        int nmRows = m_model->rowCount(nUserIndex);  //количество строк

                QModelIndex tIndex;
                tIndex=proxyModel->index(0,0,QModelIndex());
                int maxNumb=proxyModel->data(tIndex,Qt::DisplayRole).toInt();
       for(int i=0;i<nmRows;i++)
        {
           QModelIndex modIndex;
           modIndex=proxyModel->index(i,0,QModelIndex());
           int tempNumb=proxyModel->data(modIndex,Qt::DisplayRole).toInt();
           if(maxNumb<tempNumb)
           {
             maxNumb=tempNumb;
           }
           else;
        }

          maxNumb++; // Номер для нового пользователя, больше на одну цифру, чем самый большой номер пользователя, уже имеющийся в системе
          QString strNumb=QString::number(maxNumb); //перевод из целого числа в строку
          int numbSymbols=strNumb.size(); //количество символов в строке
          int addNull=5-numbSymbols;  //вычислим количество незначащих нулей
          QString addedNulls;
          switch(addNull)
          {
          case 4:addedNulls="0000";
              break;
          case 3:addedNulls="000";
              break;
          case 2:addedNulls="00";
              break;
          case 1:addedNulls="0";
              break;
          default:addedNulls="0";

          }

          nUserDialog->lineNumb->setText(addedNulls+QString::number(maxNumb));


        connect(nUserDialog,SIGNAL(nuButton()),this,SLOT(okClicked()));

    }

    void ModelViewDemoWidget::showUser()
    {

        nUserDialog=new NewUser(this);
        nUserDialog->show();
        nUserDialog->raise();
        nUserDialog->activateWindow();

       m_view->setSelectionBehavior(QAbstractItemView::SelectRows);

        QVariant myData;
        qDebug()<<myData;

        QModelIndex mIndex;
        mIndex=m_view->currentIndex();
        qDebug()<<" M = "<<mIndex;
        int ROW = mIndex.row();
        int COLUMN = mIndex.column();
        qDebug()<<" Row "<<ROW<<" Column "<<COLUMN;

        QModelIndex Top;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());

        COLUMN=0;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        nUserDialog->lineNumb->setText(proxyModel->data(Top,Qt::DisplayRole).toString());
        COLUMN=1;
         Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        nUserDialog->lineName->setText(proxyModel->data(Top,Qt::DisplayRole).toString());
        COLUMN=2;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        nUserDialog->lineSurname->setText(proxyModel->data(Top,Qt::DisplayRole).toString());
        COLUMN=3;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        nUserDialog->linePatronymic->setText(proxyModel->data(Top,Qt::DisplayRole).toString());
        COLUMN=4;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        nUserDialog->linePosition->setText(proxyModel->data(Top,Qt::DisplayRole).toString());
        COLUMN=5;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        QString Hours=proxyModel->data(Top,Qt::DisplayRole).toString();
        nUserDialog->setHours(Hours);

        COLUMN=6;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        QString Exper=proxyModel->data(Top,Qt::DisplayRole).toString();
        nUserDialog->setExperience(Exper);

        COLUMN=7;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        QString hr=proxyModel->data(Top,Qt::DisplayRole).toString();
        nUserDialog->setHrPay(hr);

        COLUMN=8;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        QString sal=proxyModel->data(Top,Qt::DisplayRole).toString();
        nUserDialog->setSalary(sal);

        COLUMN=9;
        Top=proxyModel->index(ROW,COLUMN,QModelIndex());
        QString mod_prem=proxyModel->data(Top,Qt::DisplayRole).toString();
        nUserDialog->setPremy(mod_prem);

//#################### Слот для внесения изменения в данные #####################################################
        connect(nUserDialog,SIGNAL(nuButton()),this,SLOT(okClicked()));

    }

    void ModelViewDemoWidget::openFile()
    {
        QFile mFile("users.txt");
        QString line;
        if(mFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {

           QTextStream tStream(&mFile);
           while (!tStream.atEnd())
           {
               line=tStream.readLine();
               QStringList field=line.split(' ');

               for(int i=0;i<field.size();i++)
               {
                  qDebug()<<field.size();
                  QString line1=field.at(i);
                  QString line2=field.at(i=i+1);
                  QString line3=field.at(i=i+1);
                  QString line4=field.at(i=i+1);
                  QString line5=field.at(i=i+1);
                  QString line6=field.at(i=i+1);
                  QString line7=field.at(i=i+1);
                  QString line8=field.at(i=i+1);
                  QString line9=field.at(i=i+1);
                  QString line10=field.at(i=i+1);

               m_numbEdit=new QLineEdit(line1);
               m_nameEdit=new QLineEdit(line2);
               m_surnameEdit=new QLineEdit(line3);
               m_patronymicEdit=new QLineEdit(line4);
               m_position=new QLineEdit(line5);
               m_hours=new QLineEdit(line6);
               m_hrpay=new QLineEdit(line7);
               m_premy=new QLineEdit(line8);
               m_experience=new QLineEdit(line9);
               m_salary=new QLineEdit(line10);

               m_model->appendPerson(m_numbEdit->text(),m_surnameEdit->text(),m_nameEdit->text(), m_patronymicEdit->text(),m_position->text(),m_hours->text(),m_hrpay->text(),m_premy->text(),m_experience->text(),m_salary->text());
                  }
             }
        }
        else
        {
            QMessageBox notOpenFile;
            notOpenFile.setText("File not open");
            notOpenFile.exec();
        }
        mFile.close();
    }

    void ModelViewDemoWidget::outClearAll()  //слот для отправки сигнала в personalmodel
    {

        m_model->clearAll_Slot();
    }


    //################### Запись данных в файл ##########################################
    void ModelViewDemoWidget::writeFile()
    {
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save user list"), "", tr("Persons(*.txt);;All Files(*)") );
    if(fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
           QMessageBox::information(this, tr("Unable to open file"), file.errorString());
           return;
    }
    QTextStream txStr(&file);
    QStringList stList;

    stList<<"\" \"";

    for(int y=0;y<m_view->verticalHeader()->count();y++)
    {
        stList.clear();
        for(int x=0;x<m_view->horizontalHeader()->count();x++)
        {
           if((m_view->horizontalHeader()->count()-x)!=1)
            stList<<""+m_view->model()->data(m_view->model()->index(y,x),Qt::DisplayRole).toString()+" ";
            else
             stList<<""+m_view->model()->data(m_view->model()->index(y,x),Qt::DisplayRole).toString()+"";
        }
         txStr<<stList.join("")+"\n";
    }
    file.close();
}

    //################### Экспорт  данных в файл в CSV файл ###############################
        void ModelViewDemoWidget::exportList()
        {
        QString fileName=QFileDialog::getSaveFileName(this,tr("Save user list"), "", tr("Persons(*.csv);;All Files(*)") );
        if(fileName.isEmpty())
        {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
               QMessageBox::information(this, tr("Unable to open file"), file.errorString());
               return;
        }
        QTextStream txStr(&file);
        QStringList stList;

        stList<<"\" \"";

        for(int i=0;i<m_view->horizontalHeader()->count();i++)
        {
            stList<<"\""+m_view->model()->headerData(i,Qt::Horizontal).toString()+"\"";
            txStr<<stList.join(";")+"\n";
        }

        for(int y=0;y<m_view->verticalHeader()->count();y++)
        {
            stList.clear();
            stList<<"\""+m_view->model()->headerData(y,Qt::Vertical).toString()+"\"";
            for(int x=0;x<m_view->horizontalHeader()->count();x++)
            {
                stList<<"\""+m_view->model()->data(m_view->model()->index(y,x),Qt::DisplayRole).toString()+"\"";
            }
            txStr<<stList.join(";")+"\n";
        }
        file.close();
    }
//###########################################################################
    void ModelViewDemoWidget::findData()
    {
        findUser=new FindWindow();
        findUser->show();
        findUser->raise();
        findUser->activateWindow();


        connect(findUser, SIGNAL(findSignal()), this, SLOT(finding()));

    }

    void ModelViewDemoWidget::setFind()
    {
        emit FSignal();
    }

    void ModelViewDemoWidget::finding()
    {

        QString findObject;
        findObject=findUser->getFind();
        QModelIndex findIndex;
        findIndex=m_view->currentIndex();
        QModelIndex FindIndex;
        FindIndex=m_view->currentIndex();
        int nmRows = m_model->rowCount(FindIndex);
        int numb=0; //переменная , если равна 0, то ничего не найдено и выскочит окно с соотвествующим сообщением

       for(int i=0;i<nmRows;i++)
        {
          for(int y=0;y<9;y++)
          {
             QModelIndex fIndx;
              fIndx=m_model->index(i,y,QModelIndex());
            QString FindStr=m_model->data(fIndx,Qt::DisplayRole).toString();
            qDebug()<<FindStr;
            if(findObject==FindStr)
            {
                numb++;
                fIndx=m_model->index(i,0,QModelIndex());
                QString f_Numb=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,1,QModelIndex());
                QString f_Family=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,2,QModelIndex());
                QString f_Name=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,3,QModelIndex());
                QString f_Patronymic=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,4,QModelIndex());
                QString f_Position=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,5,QModelIndex());
                QString f_Hours=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,6,QModelIndex());
                QString f_Hrpay=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,7,QModelIndex());
                QString f_Premy=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,8,QModelIndex());
                QString f_Experience=m_model->data(fIndx,Qt::DisplayRole).toString();
                fIndx=m_model->index(i,9,QModelIndex());
                QString f_Salary=m_model->data(fIndx,Qt::DisplayRole).toString();

                findUser->insFinders(f_Numb, f_Family, f_Name, f_Patronymic, f_Position, f_Hours, f_Hrpay, f_Premy, f_Experience, f_Salary);

            }
            else
            {

            }
          }
        }
            if(numb==0)
            {
                QMessageBox msgBox;
                msgBox.setText("Nothing find");
                msgBox.exec();
                return;
            }
            else;
            numb=0;
    }
//#################################### Переписать слот ,удаляет из представления но не удаляет из модели ###########################
    void ModelViewDemoWidget::delUser()
    {

                     QModelIndex dIndex;
                     dIndex=m_view->currentIndex();
                     int dRow=dIndex.row();
             //      m_model->beginRemoveRows(const dIndex,dRow,dRow);
                     QMessageBox::warning(this, trUtf8("Удаление записи"), trUtf8("Do you really delete this record?"), QMessageBox::Yes | QMessageBox::No)==QMessageBox::No;
                     m_model->removeRow(dRow);
             //      m_model->endRemoveRows();
                     m_view->setRowHidden(dRow, true);

                     qDebug()<<"ROW = "<<dRow;

    }
//############################  Слот контекстного меню  ########################################################################################
    void ModelViewDemoWidget::slotCustomContextMenu(QPoint pos)
    {
        menu=new QMenu(tr("&Delete"));
        addContextUser=new QAction("Add new user", this);
        showContextUser=new QAction("Show user", this);
        delContextUser=new QAction("Delete", this);

        menu->addAction(newUserAction);
        menu->addAction(showContextUser);        
        menu->addAction(delContextUser);

        connect(showContextUser, SIGNAL(triggered()), this, SLOT(showUser()));
        connect(delContextUser, SIGNAL(triggered()), this, SLOT(delUser()));
//######################## Вызов контекстного меню  ####################################################################################
        menu->popup(m_view->viewport()->mapToGlobal(pos));
    }
