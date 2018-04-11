#ifndef LISTAALBUNS_H
#define LISTAALBUNS_H

#include <QVector>
#include <QString>

#include "album.h"
#include "foto.h"
#include "pagina.h"
class Album;
class Pagina;
enum pageType_t : short int;
class Foto;
class GestorBD;

class ListaAlbuns
{
public:
    ListaAlbuns(GestorBD* gestor=0);
    //~ListaAlbuns();

    Album* createAlbum(QString name, QString desc, QDir path, pageType_t type);

    /* REMOVE AND EDIT NOT YET IMPLEMENTED
    int deleteAlbum(Album* album);
    int editAlbum(Album* album, QString newName, QString newDesc);
    */

    QVector<Album*> getAlbums();


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

    QVector<Album*> Albums;
    GestorBD* oGestor;

    int generateID(QVector<int> &allocatedID, int &maxID); // pode alterar maxID
    int genAlbumID();/*{
        return generateID(allocatedAlbumID, maxAlbumID);
    }*/

    int genPageID();/*{
        return generateID(allocatedPageID, maxPageID);
    }*/

    int genPhotoID();/*{
        return generateID(allocatedPhotoID, maxPhotoID);
    }*/
};

#endif // LISTAALBUNS_H
