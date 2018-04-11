#ifndef FOTO_H
#define FOTO_H

#include <QString>
#include <QVector>
#include <QDir>

class ListaPessoas;
class GestorBD;
class Pessoa;
class Pagina;

class Foto
{
public:

    Foto(int id, QDir Dir, Pagina* parent = 0, GestorBD* gestor = 0);

    int deleteSelf();

    int getID();
    QDir getPath();

    QVector<Pessoa*> getPeople();

    Pagina* parent();

    /*ASSOCIATIONS NOT YET IMPLEMENTED
    int acceptPerson(Pessoa* Person);
    int removePerson(Pessoa* Person);
    */

private:

    int ID;
    QDir Path;
    QVector<Pessoa*> People;

    ListaPessoas* PeopleList;//Como se lá chega?????????
    GestorBD* oGestor;
    Pagina* Parent;

};

#endif // FOTO_H
