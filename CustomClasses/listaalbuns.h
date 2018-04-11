#ifndef LISTAALBUNS_H
#define LISTAALBUNS_H

#include "album.h"

class ListaAlbuns
{
public:
    ListaAlbuns(GestorBD* gestor=0);
    ~ListaAlbuns();

    //----------------Get Atributes----------------//

    QVector<Album*> getAlbums();

    //-------------------Create--------------------//

    Album* createAlbum(AlbumParam atributes);

    Pagina* createPage(PageParam atributes, Album* destination=0);

    Foto* createPhoto(PhotoParam atributes,Pagina* destPage, Album* destAlbum);

    /* REMOVE AND EDIT NOT YET IMPLEMENTED
    int deleteAlbum(Album* album);
    int editAlbum(Album* album, QString newName, QString newDesc);
    */
    /* MOVE AND SEARCH NOT YET IMPLEMENTED
    int movePage(Album* origin, Album* destination, Pagina* page);

    int movePhoto(Album* originAlbum, Pagina* originPage,
                  Album* destinationAlbum, Pagina* destinationPage,
                  Foto* photo);
    QVector<Foto*> searchPhotoByDate(QDate);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */

private:

    QVector<int> allocatedAlbumID;
    int maxAlbumID;

    QVector<int> allocatedPageID;
    int maxPageID;

    QVector<int> allocatedPhotoID;
    int maxPhotoID;

    int generateID(QVector<int> &allocatedID, int &maxID);
    int genAlbumID();
    int genPageID();
    int genPhotoID();

    QVector<Album*> Albums;
    GestorBD* oGestor;
};

#endif // LISTAALBUNS_H
