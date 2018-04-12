#include "mainwindow.h"
#include <QApplication>

#include "CustomClasses/listaalbuns.h"
#include "CustomClasses/listapessoas.h"

QDir DBPath("BaseDeDados.db");


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    GestorBD*       oGestor      = new GestorBD(DBPath.path());
    ListaPessoas*   aListaPessoas= new ListaPessoas(oGestor);
    ListaAlbuns*    aListaAlbuns = new ListaAlbuns(oGestor);

 //=================================
    w.show();
    return a.exec();
}
