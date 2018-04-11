#ifndef PAGINA_H
#define PAGINA_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDir>

class GestorBD;
class Album;
class Foto;

enum pageType_t : short int { viagem, festa, coisaPessoa, outro };

class Pagina
{
public:

    Pagina(int id, QString desc, QDir path, Album* parent=0,GestorBD* gestor = 0);

    int deleteSelf();

    int getID();
    QString getDescription();
    QDir getPath();
    virtual pageType_t getType()=0;

    QVector<Foto*> getPhotos();

    Album* parent();


    int acceptPhoto(Foto* photo);

    /* DELETE AND MOVE NOT YET IMPLEMENTED
    int removePhoto(Foto* photo);
    int deletePhoto(Foto* photo);
    */

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


protected:

    int createFolder(QString folderName);
    virtual QString createFolderName();

    QString Description;
    int ID;
    QDir Path;

    Album* Parent;
    GestorBD* oGestor;
    QVector<Foto*> Photos;
};


class PaginaViagem : public Pagina
{
public:

    PaginaViagem(int id, QString desc, QDir path, QDateTime start, QDateTime end, Album* parent=0,GestorBD* gestor = 0);

    QDate getStartDate(){
        return StartDate;
    }
    QDate getEndDate(){
        return EndDate;
    }
    pageType_t getType(){
        return viagem;
    }

private:
    QString createFolderName();

    QDate StartDate;
    QDate EndDate;

};


class PaginaFesta : public Pagina
{
public:

    PaginaFesta(int id, QString desc, QDir path, QDateTime date, QString type, Album* parent=0,GestorBD* gestor = 0);

    QDate getDate(){
        return Date;
    }
    QString getPartyType(){
        return PartyType;
    }
    pageType_t getType(){
        return festa;
    }

private:
    QString createFolderName();

    QDate Date;
    QString PartyType;

};


class PaginaCoisaPessoa : public Pagina
{
public:

    PaginaCoisaPessoa(int id, QString desc, QDir path, Album* parent=0,GestorBD* gestor = 0);

    pageType_t getType(){
        return coisaPessoa;
    }

private:
    QString createFolderName();

};

class PaginaOutro : public Pagina
{
public:

    PaginaOutro(int id, QString desc, QDir path, QDateTime start,QDateTime end, Album* parent=0,GestorBD* gestor = 0);

    QDate getStartDate(){
        return StartDate;
    }
    QDate getEndDate(){
        return EndDate;
    }
    pageType_t getType(){
        return outro;
    }
private:
    QString createFolderName();

    QDate StartDate;
    QDate EndDate;
};


#endif // PAGINA_H
