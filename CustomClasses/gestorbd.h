#ifndef GESTORBD_H
#define GESTORBD_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "paramstructs.h"
#include "flags.h"

extern QDir DBPath;

class GestorBD
{
public:

    //constructor
    GestorBD(const QString& path);

    //destructor
    ~GestorBD();

    //Cria Tabelas
    bool createTables();

    //-------------------------------------------------------------
    //ADD
    //-------------------------------------------------------------
    bool addPhoto(PhotoParam*);

    bool addAlbum(AlbumParam*);

    bool addPage(PageParam*);

    bool addPerson(PersonParam*);
    //-------------------------------------------------------------
    //UPDATE
    //-------------------------------------------------------------
    bool updatePhoto(PhotoParam*);

    bool updateAlbum(AlbumParam*);

    bool updatePage(PageParam*);

    bool updatePerson(PersonParam*);

    //-------------------------------------------------------------
    //GET
    //-------------------------------------------------------------
    QVector<PhotoParam *> *getPhotos(PageParam *);

    QVector<PageParam *> *getPages(AlbumParam *);

    QVector<AlbumParam *> *getAlbums(ListaAlbuns *);

    QVector<PersonParam *> *getPeople(ListaPessoas *);


    //-------------------------------------------------------------
    //DELETE
    //-------------------------------------------------------------
    bool deletePhoto(PhotoParam*);

    bool deleteAlbum(AlbumParam*);

    bool deletePage(PageParam*);

    bool deletePerson(PersonParam*);

    //-------------------------------------------------------------
    //OTHERS
    //-------------------------------------------------------------
    bool removeAll();

    bool clearAll();

    bool isOpen() const;

    bool updateAtachment(const QString& , const QString&, const QString &);

    bool addAtachment(const QString& ,const QString&);

    bool getPeopleByFoto(const QString&);

    bool getAtachments();

private:
    QSqlDatabase m_db;
};

#endif // GESTORBD_H
