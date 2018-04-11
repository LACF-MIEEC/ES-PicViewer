#ifndef GESTORBD_H
#define GESTORBD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "foto.h"
#include "pagina.h"
#include "pessoa.h"
#include "album.h"
#include "listaalbuns.h"
#include "listapessoas.h"

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
    //GET
    //-------------------------------------------------------------
    bool addFoto(Foto     *newFoto);

    bool addAlbum(Album   *newAlbum);

    bool addPagina(Pagina *newPagina);

    bool addPessoa(Pessoa *newPessoa);
    //-------------------------------------------------------------
    //GET
    //-------------------------------------------------------------
    bool updateFoto(Foto *newFoto);

    bool updateAlbum(Album   *newAlbum);

    bool updatePagina(Pagina *newPagina);

    bool updatePessoa(Pessoa *newPessoa);

    //-------------------------------------------------------------
    //GET
    //-------------------------------------------------------------
    QVector<Foto*> getFotos(Pagina* Page);

    QVector<Pagina*>  getPaginas(Album* Alb);

    QVector<Album*> getAlbuns(ListaAlbuns* Albs);

    QVector<Pessoa*> getPessoas(ListaPessoas* People);


    //-------------------------------------------------------------
    //DELETE
    //-------------------------------------------------------------
    bool deleteFoto(Foto *delFoto);

    bool deleteAlbum(Album *delAlbum);

    bool deletePagina(Pagina *delPagina);

    bool deletePessoa(Pessoa *delPessoa);

    //-------------------------------------------------------------
    //OTHERS
    //-------------------------------------------------------------
    bool removeAll();

    bool clearAll();

    bool isOpen() const;

    bool updateAtachment(const QString& , const QString&, const QString &);

    bool addAtachment(const QString& ,const QString&);

    bool getPessoasByFoto(const QString&);

    bool getAtachments();

private:
    QSqlDatabase m_db;
};

#endif // GESTORBD_H
