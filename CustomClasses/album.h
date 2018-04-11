#ifndef ALBUM_H
#define ALBUM_H

#include <QVector>
#include <QString>
#include <QDir>

//#include "foto.h"
//#include "pagina.h"
//#include "listaalbuns.h"
//#include "gestorbd.h"

class Foto;
class Pagina;
enum pageType_t : short int;
class ListaAlbuns;
class GestorBD;


class Album
{
public:

    Album(int id, QString name, QString desc, QDir path, pageType_t type, ListaAlbuns* parent =0, GestorBD* gestor =0);

    int deleteSelf();

    /* MODIFICATIONS NOT YET IMPLEMENTED
    int setName(QString newName);
    void setDescription(QString newDesc);
    */

    int getID();
    QString getName();
    QString getDescription();
    QDir getPath();
    pageType_t getPageType();

    QVector<Pagina*> getPages();

    ListaAlbuns* parent();

    int acceptPage(Pagina* page);

    /* DELETE AND MOVE NOT YET IMPLEMENTED
    int removePage(Pagina* page);
    int deletePage(Pagina* page);
    */

    //int acceptPhoto(Pagina* page, Foto* photo); //Mais vale ir logo à página se já tenho o ponteiro

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate date);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


private:

    int createFolder();
    QString createFolderName();

    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;

    ListaAlbuns* aListaAlbuns;
    GestorBD* oGestor;
    QVector<Pagina*> Pages;

};

#endif // ALBUM_H
