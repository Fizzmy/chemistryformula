#include "mainwindow.h"
#include<check.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    check *checkPage= new check();
    w.putwidget(checkPage);
    w.show();
    return a.exec();
}
