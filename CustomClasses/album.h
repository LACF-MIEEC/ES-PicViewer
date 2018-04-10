#ifndef ALBUM_H
#define ALBUM_H

#include <QVector>
#include <string> // Ou o que for preciso para o tipo de string que se usar
// Search & Replace std::string por std::string, ou assim

//#include "foto.h"
class Foto;
struct FotoParams;

//#include "pagina.h"
class Pagina;
struct PaginaParams;
enum pageType_t : short int;

//#include "listaalbuns.h"
class ListaAlbuns;

//#include "gestorbd.h"
class GestorBD;

struct AlbumParams {
    int albumID;
    std::string Name; // ou outro tipo de string
    GestorBD* oGestor;
    ListaAlbuns* aListaAlbuns;
    //...
};

class Album
{
public:
    // TODO: tipos de return
    Album(AlbumParams params);

    //~Album();


    int deleteSelf(); //Remover-se da base de dados, remover suas paginas, apagar pasta...

    int setName(std::string newName);
    void setDescription(std::string newDesc);

    QVector<Pagina*> getPages();
    pageType_t getPageType();

    Pagina* createPage(PaginaParams params);
    int acceptPage(Pagina* page);
    int removePage(Pagina* page);
    int deletePage(Pagina* page);

    QVector<Foto*> searchPhotoByDate(/*Date*/);
    QVector<Foto*> searchPhotoByKeyword(std::string keyword);


    Foto* createPhoto(FotoParams params);
    int acceptPhoto(Pagina* page, Foto* photo);


private:

    int createFolder();
    std::string createFolderName();

    int albumID;

    ListaAlbuns* aListaAlbuns;
    GestorBD* oGestor;
    QVector<Pagina*> pages;


    pageType_t pageType; // enum definido em pagina.h
};

#endif // ALBUM_H
