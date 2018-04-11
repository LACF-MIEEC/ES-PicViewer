#ifndef LISTAPESSOAS_H
#define LISTAPESSOAS_H

#include <QVector>
#include <QString>

#include "pessoa.h"
#include "foto.h"

class GestorBD;

class ListaPessoas
{
public:
    ListaPessoas(GestorBD* gestor=0);

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotosByPerson(QString name);
    */
    Pessoa* createPerson(QString name, QDate birth, gender gen, QString bond);

    /* REMOVE AND ATTACHMENTS NOT YET IMPLEMENTED
    int deletePerson(Pessoa*);

    int attachPerson(Pessoa* person, Foto* foto);
    int dettachPerson(Pessoa* person, Foto* foto);
    */


private:

    QVector<int> allocatedPeopleID;
    int maxPeopleID;

    int generateID(QVector<int> &allocatedID, int &maxID); // pode alterar maxID
    int genPersonID();
    QVector<Pessoa*> People;
    GestorBD* oGestor;
};

#endif // LISTAPESSOAS_H
