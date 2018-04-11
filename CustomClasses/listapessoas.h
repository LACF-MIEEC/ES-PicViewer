#ifndef LISTAPESSOAS_H
#define LISTAPESSOAS_H


#include "pessoa.h"

class GestorBD;

class ListaPessoas
{
public:
    ListaPessoas(GestorBD* gestor=0);
    ~ListaPessoas();
    //----------------Get Atributes----------------//

    QVector<Pessoa*> getPeople();

    //-------------------Create--------------------//

    Pessoa* createPerson(PersonParam atributes);

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotosByPerson(QString name);
    */
    /* REMOVE AND ATTACHMENTS NOT YET IMPLEMENTED
    int deletePerson(Pessoa*);

    int attachPerson(Pessoa* person, Foto* foto);
    int dettachPerson(Pessoa* person, Foto* foto);
    */


private:

    QVector<int> allocatedPeopleID;
    int maxPeopleID;

    int generateID(QVector<int> &allocatedID, int &maxID);
    int genPersonID();

    QVector<Pessoa*> People;
    GestorBD* oGestor;
};

#endif // LISTAPESSOAS_H
