#ifndef PESSOA_H
#define PESSOA_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDir>
#include <QDebug>

#include "gestorbd.h"

class Pessoa
{
public:
    Pessoa(PersonParam atributes);

    void deleteSelf();

    //----------------Get Atributes----------------//

    int getID();
    QString getName();
    QDate getBirth();
    gender getGender();
    QString getBond();

    QVector<Foto*> getPhotos();

    ListaPessoas* parent();

    /* ATTACHMENTS NOT YET IMPLEMENTED
    int acceptPhoto(Foto* photo);
    */
    /* REMOVE NOT YET IMPLEMENTED
    int removePhoto(Foto* photo);
    */

private:

    int ID;
    QString Name;
    QDate Birth;
    gender Gender;
    QString Bond;

    ListaPessoas *Parent;
    GestorBD* oGestor;
    QVector<Foto*> Photos;
};

#endif // PESSOA_H
