#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunMode.setFlag(Setup::Boot);
    MainWindow w;
    RunMode.setFlag(Setup::RunTime);


 //=================================
    w.show();
    return a.exec();
}
