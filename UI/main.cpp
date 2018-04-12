#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RunMode.setFlag(Setup::Boot);
    MainWindow w;
    RunMode.setFlag(Setup::RunTime);



//    GestorBD*       oGestor      = new GestorBD(DBPath.path());
//    ListaPessoas*   aListaPessoas= new ListaPessoas(oGestor);
//    ListaAlbuns*    aListaAlbuns = new ListaAlbuns(oGestor);

 //=================================
    w.show();
    return a.exec();
}
