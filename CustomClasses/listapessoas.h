#ifndef LISTAPESSOAS_H
#define LISTAPESSOAS_H

#include <QVector>
#include <string>

#include "pessoa.h"
#include "foto.h"

class ListaPessoas
{
public:
    ListaPessoas();


    QVector<Foto*> searchPhotosByPerson(std::string name);

    Pessoa* createPerson(PessoaParams params);
    int deletePerson(Pessoa*);

    int attachPerson(Pessoa* person, Foto* foto);
    int dettachPerson(Pessoa* person, Foto* foto);


private:
    QVector<Pessoa*> people;
};

#endif // LISTAPESSOAS_H
