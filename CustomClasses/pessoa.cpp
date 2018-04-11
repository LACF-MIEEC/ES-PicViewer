#include "pessoa.h"

Pessoa::Pessoa(int id, QString name, QDate birth, gender gen, QString bond, ListaPessoas *parent=0, GestorBD *gestor=0)
{
    ID=id;
    Name=name;
    Birth=birth;
    Gender=gen;
    Bond=bond;
    Parent=parent;
    oGestor=gestor;
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
QVector<Foto*> Pessoa::getPhotos(){
    return Photos;
}
ListaPessoas* Pessoa::parent(){
    return Parent;
}
