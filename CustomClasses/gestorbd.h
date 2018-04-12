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
    bool addPhoto(Foto     *newFoto);

    bool addAlbum(Album   *newAlbum);

    bool addPage(Pagina *newPagina);

    bool addPerson(Pessoa *newPessoa);
    //-------------------------------------------------------------
    //UPDATE
    //-------------------------------------------------------------
    bool updatePhoto(Foto *newFoto);

    bool updateAlbum(Album *newAlbum);

    bool updatePage(Pagina *newPagina);

    bool updatePerson(Pessoa *newPessoa);

    //-------------------------------------------------------------
    //GET
    //-------------------------------------------------------------
    QVector<PhotoParam*> getPhotos(Pagina* Page);

    QVector<PageParam *> getPages(Album* Alb);

    QVector<AlbumParam*> getAlbums(ListaAlbuns* Albs);

    QVector<PersonParam *> getPeople(ListaPessoas* People);


    //-------------------------------------------------------------
    //DELETE
    //-------------------------------------------------------------
    bool deletePhoto(Foto *delFoto);

    bool deleteAlbum(Album *delAlbum);

    bool deletePage(Pagina *delPagina);

    bool deletePerson(Pessoa *delPessoa);

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
