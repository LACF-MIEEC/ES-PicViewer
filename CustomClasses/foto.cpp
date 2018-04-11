#include "foto.h"

Foto::Foto(PhotoParam atributes)
{
    ID      = atributes.ID;
    Path    = atributes.Path;
    Parent  = atributes.Parent;
    oGestor = atributes.Gestor;

}

void Foto::deleteSelf(){

    delete this;
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

Pagina* Foto::parent(){
    return Parent;
}

