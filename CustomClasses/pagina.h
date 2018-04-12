#ifndef PAGINA_H
#define PAGINA_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "foto.h"

class Pagina
{
public:

    Pagina(PageParam atributes);

    void deleteSelf();

    //----------------Get Atributes----------------//

    int getID();
    QString getDescription();
    QDir getPath();

    virtual pageType_t getType()=0;

    virtual QDate getStartDate()=0;
    virtual QDate getEndDate()=0;
    virtual QString getPartyType()=0;

    QVector<Foto*> getPhotos();

    Album* parent();

    //-------------------Create--------------------//

    Foto* createPhoto(PhotoParam atributes);


    /* DELETE AND MOVE NOT YET IMPLEMENTED
     * int acceptPhoto(Foto* photo);
    int removePhoto(Foto* photo);
    int deletePhoto(Foto* photo);
    */
    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


protected:

    Setup::RunStates RunMode = Setup::Boot;

    int createFolder(QString folderName);
    virtual QString createFolderName()=0;

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

    PaginaViagem(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:

    QString createFolderName();

    QDate StartDate;
    QDate EndDate;

};

class PaginaFesta : public Pagina
{
public:

    PaginaFesta(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

    QDate Date;
    QString PartyType;

};

class PaginaCoisaPessoa : public Pagina
{
public:

    PaginaCoisaPessoa(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

};

class PaginaOutro : public Pagina
{
public:

    PaginaOutro(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

    QDate StartDate;
    QDate EndDate;
};


#endif // PAGINA_H
