#include "modelviewdemowidget.h"
#include "personsmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModelViewDemoWidget w;
    w.show();
    return a.exec();
}
