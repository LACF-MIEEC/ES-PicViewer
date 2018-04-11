#ifndef FOTO_H
#define FOTO_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>


#include "flags.h"
#include "gestorbd.h"

class ListaPessoas;
class GestorBD;
class Pessoa;
class Pagina;

struct PhotoParam{
    int ID;
    QDir Path;
    Pagina* Parent;
    GestorBD* Gestor;
};
class Foto
{
public:

    Foto(PhotoParam atributes);

    void deleteSelf();


    //----------------Get Atributes----------------//

    int getID();
    QDir getPath();

    QVector<Pessoa*> getPeople();

    Pagina* parent();

    /*ASSOCIATIONS NOT YET IMPLEMENTED
    int acceptPerson(Pessoa* Person);
    int removePerson(Pessoa* Person);
    */

private:

    Setup::RunStates RunMode = Setup::Boot;

    int ID;
    QDir Path;
    QVector<Pessoa*> People;

    ListaPessoas* PeopleList;//Como se lá chega?????????
    GestorBD* oGestor;
    Pagina* Parent;

};

#endif // FOTO_H
