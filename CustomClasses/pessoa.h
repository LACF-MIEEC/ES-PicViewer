#ifndef PESSOA_H
#define PESSOA_H

#include <QVector>
#include <string>

#include "listaalbuns.h"
#include "gestorbd.h"
//#include "foto.h"
class Foto;

struct PessoaParams{
    std::string name;
    //...
};

class Pessoa
{
public:
    Pessoa(PessoaParams params);

    int acceptPhoto(Foto* photo); // no SAD está acceptPhotos()
    int removePhoto(Foto* photo); // no SAD está removePhotos()
    QVector<Foto*> getPhotos();

    // getters e setters conforme necessário
private:
    std::string name;

    ListaAlbuns* aListaAlbuns;
    GestorBD* oGestor;
    QVector<Foto*> fotos;
};

#endif // PESSOA_H
