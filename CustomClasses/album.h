#ifndef ALBUM_H
#define ALBUM_H

#include "pagina.h"

class ListaAlbuns;
class GestorBD;

struct AlbumParam{
    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;
    ListaAlbuns* Parent =0;
    GestorBD* Gestor =0;
};

class Album
{
public:

    Album(AlbumParam atributes);

    void deleteSelf();

    //----------------Get Atributes----------------//

    int getID();
    QString getName();
    QString getDescription();
    QDir getPath();
    pageType_t getPageType();

    QVector<Pagina*> getPages();

    ListaAlbuns* parent();

    //-------------------Create--------------------//

    Pagina* createPage(PageParam atributes);

    Foto* createPhoto(PhotoParam atributes, Pagina* destination);



    /* MODIFICATIONS NOT YET IMPLEMENTED
    int setName(QString newName);
    void setDescription(QString newDesc);
    */

    /* DELETE AND MOVE NOT YET IMPLEMENTED
    int acceptPage(Pagina* page);
    int removePage(Pagina* page);
    int deletePage(Pagina* page);
    */

    //int acceptPhoto(Pagina* page, Foto* photo); //Mais vale ir logo à página se já tenho o ponteiro

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate date);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


private:

    Setup::RunState RunMode = Setup::Boot;

    int createFolder(QString folderName);
    QString createFolderName();

    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;

    ListaAlbuns* Parent;
    GestorBD* oGestor;
    QVector<Pagina*> Pages;

};

#endif // ALBUM_H
