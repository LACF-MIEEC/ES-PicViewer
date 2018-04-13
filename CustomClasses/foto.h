#ifndef FOTO_H
#define FOTO_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "gestorbd.h"
#include "listapessoas.h"


class Foto
{
public:

    Foto(PhotoParam atributes);
    ~Foto();


    //----------------Get Atributes----------------//

    int getID();
    QDir getPath();

    QVector<Pessoa *> *getPeople();

    Pagina* parent();

    /*ASSOCIATIONS NOT YET IMPLEMENTED
    int acceptPerson(Pessoa* Person);
    int removePerson(Pessoa* Person);
    */

private:

    int ID;
    QDir Path;
    QVector<Pessoa*> *People;

    ListaPessoas* PeopleList;//Como se lá chega?????????
    GestorBD* oGestor;
    Pagina* Parent;

};

#endif // FOTO_H
