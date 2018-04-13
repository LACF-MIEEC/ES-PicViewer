#include "foto.h"

Foto::Foto(PhotoParam atributes)
{
    ID      = atributes.ID;
    Path    = atributes.Path;
    Parent  = atributes.Parent;
    oGestor = atributes.Gestor;

    People = new QVector<Pessoa*>();
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

QVector<Pessoa*>* Foto::getPeople(){
    return People;
}

Pagina* Foto::parent(){
    return Parent;
}

