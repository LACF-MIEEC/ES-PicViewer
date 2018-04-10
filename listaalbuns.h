#ifndef LISTAALBUNS_H
#define LISTAALBUNS_H

#include <QVector>

//#include "album.h"
class Album;
struct AlbumParams;

//#include "pagina.h"
class Pagina;
struct PaginaParams;

//#include "foto.h"
class Foto;
struct FotoParams;


class ListaAlbuns
{
public:
    ListaAlbuns();






    Album* createAlbum(AlbumParams params);
    int deleteAlbum(Album* album);
    int editAlbum(Album* album, std::string newName, std::string newDesc);
    QVector<Album*> getAlbuns();

    Pagina* createPage(PaginaParams params);
    int movePage(Album* origin, Album* destination, Pagina* page);

    int movePhoto(Album* originAlbum, Pagina* originPage,
                  Album* destinationAlbum, Pagina* destinationPage,
                  Foto* photo);
    QVector<Foto*> searchPhotoByDate(/*Date*/);
    QVector<Foto*> searchPhotoByKeyword(std::string keyword);



    int genAlbumID();/*{
        return generateID(allocatedAlbumID, maxAlbumID);
    }*/

    int genPageID();/*{
        return generateID(allocatedPageID, maxPageID);
    }*/

    int genPhotoID();/*{
        return generateID(allocatedPhotoID, maxPhotoID);
    }*/

private:
    QVector<int> allocatedAlbumID;
    int maxAlbumID;

    QVector<int> allocatedPageID;
    int maxPageID;

    QVector<int> allocatedPhotoID;
    int maxPhotoID;

    QVector<Album*> albuns;
    //typedef QVector<int> testType;
    int generateID(QVector<int> &allocatedID, int &maxID); // pode alterar maxID
};

#endif // LISTAALBUNS_H
