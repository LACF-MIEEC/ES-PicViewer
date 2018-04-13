#include "gestorbd.h"
#include "foto.h"
#include "pagina.h"
#include "album.h"
#include "listaalbuns.h"
#include "listapessoas.h"
#include "pessoa.h"

Pessoa::Pessoa(PersonParam atributes)
{
    ID      =   atributes.ID;
    Name    =   atributes.Name;
    Birth   =   atributes.Birth;
    Gender  =   atributes.Gender;
    Bond    =   atributes.Bond;
    Parent  =   atributes.Parent;
    oGestor =   atributes.Gestor;

    Photos = new QVector<Foto*>();
}

Pessoa::~Pessoa(){
    delete Photos;
}

int Pessoa::getID(){
    return ID;
}
QString Pessoa::getName(){
    return Name;
}
QDate Pessoa::getBirth(){
    return Birth;
}
gender Pessoa::getGender(){
    return Gender;
}
QString Pessoa::getBond(){
    return Bond;
}
QVector<Foto*>* Pessoa::getPhotos(){
    return Photos;
}
ListaPessoas* Pessoa::parent(){
    return Parent;
}
