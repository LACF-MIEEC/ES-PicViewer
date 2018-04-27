
#include "gestorbd.h"
#include "foto.h"
#include "pagina.h"
#include "album.h"
#include "listaalbuns.h"
#include "listapessoas.h"
#include "pessoa.h"


Foto::Foto(PhotoParam atributes)
{
    ID      = atributes.ID;
    Path    = atributes.Path;
    Parent  = atributes.Parent;
    oGestor = atributes.Gestor;

    People = QVector<Pessoa*>();
}

Foto::~Foto(){
    delete People;
}

int Foto::getID(){
    return ID;
}

QDir Foto::getPath(){
    return Path;
}

QVector<Pessoa*> Foto::getPeople(){
    return People;
}

int Foto::getParentID(){
    return Parent->getID();
}

Pagina* Foto::parent(){
    return Parent;
}

