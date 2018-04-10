#ifndef PAGINA_H
#define PAGINA_H

#include <string>
#include <QVector>


//#include "gestorbd.h"
class GestorBD;

//#include "listaalbuns.h"
class ListaAlbuns;

//#include "album.h"
class Album;

//#include "foto.h"
class Foto;
struct FotoParams;




enum pageType_t : short int { viagem, festa, coisaPessoa, outro };

struct PaginaParams{
    int pageID;
    //...

};

class Pagina
{
public:
    //std::string para algum tipo fancy de string?
    Pagina(PaginaParams);
    //~Pagina();
    int deleteSelf(); // Remover da B.D., etc

    int createPhoto(FotoParams photo);
    int acceptPhoto(Foto* photo);
    int removePhoto(Foto* photo);
    int deletePhoto(Foto* photo);

    void attachPerson(); // ???
    void detachPerson(); // ???

    QVector<Foto*> getPhotos();
    QVector<Foto*> searchPhotoByDate(/*Date*/);
    QVector<Foto*> searchPhotoByKeyword(std::string keyword);

    int getID();
    PaginaParams getAttributes(); // getters mais especificos?
    pageType_t getType(); // Reimplementada por cada subClasse
    //void getAttributes(); // --- Repetida no SAD

protected:  // Por causa das heranças
    int createFolder(); // Não está no SAD, mas imagino que seja preciso
    std::string createFolderName();

    std::string description;
    int pageID;
    // ...
    Album* parent;
    ListaAlbuns* aListaAlbuns;
    GestorBD* oGestor;
    QVector<Foto*> photos;
};


class PaginaViagem : public Pagina
{
public:
    // Definições podem ser passadas para o .cpp
    PaginaViagem(PaginaParams params);/* : Pagina(params) {
        //atributos especificos deste tipo
    }*/

    pageType_t getType();/*{
        return viagem;
    }*/

private:
    std::string createFolderName();

};


class PaginaFesta : public Pagina
{
public:
    // Definições podem ser passadas para o .cpp
    PaginaFesta(PaginaParams params) : Pagina(params) {
        //atributos especificos deste tipo
    }

    pageType_t getType(){
        return festa;
    }

private:
    std::string createFolderName();

};


class PaginaCoisaPessoa : public Pagina
{
public:
    // Definições podem ser passadas para o .cpp
    PaginaCoisaPessoa(PaginaParams params) : Pagina(params) {
       //atributos especificos deste tipo
    }

    pageType_t getType(){
        return coisaPessoa;
    }

private:
    std::string createFolderName();

};


class PaginaOutro : public Pagina
{
public:
    // Definições podem ser passadas para o .cpp
    PaginaOutro(PaginaParams params) : Pagina(params) {
        //atributos especificos deste tipo
    }

    pageType_t getType(){
        return outro;
    }
private:
    std::string createFolderName();

};


#endif // PAGINA_H
