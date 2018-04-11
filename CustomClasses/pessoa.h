#ifndef PESSOA_H
#define PESSOA_H

#include <QVector>
#include <QString>
#include <QDate>

class GestorBD;
class Foto;
class ListaPessoas;

enum gender :short int {feminino, masculino};

class Pessoa
{
public:
    Pessoa(int id, QString name, QDate birth, gender gen, QString bond, ListaPessoas *parent=0, GestorBD *gestor=0);
    //~Pessoa();

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
