#ifndef GESTORBD_H
#define GESTORBD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class GestorBD
{
public:

    //constructor
    GestorBD(const QString& path);

    //destructor
    ~GestorBD();

    bool isOpen() const;

    bool createTables();

    bool addFoto(const QString& ,const QString& ,const QString& ,const QString&);

    bool addAtachment(const QString& ,const QString&);

    bool addAlbum(const QString& ,const QString& ,const QString& ,const QString&,const QString&);

    bool addPagina(const QString& ,const QString& ,const QString&);

    bool addPessoa(const QString& ,const QString& ,const QString& ,const QString&);

    bool updateFoto(const QString& ,const QString& ,const QString& ,const QString&);

    bool updateAtachment(const QString& , const QString&, const QString &);

    bool updateAlbum(const QString& ,const QString& ,const QString& ,const QString&,const QString&);

    bool updatePagina(const QString& ,const QString& ,const QString&);

    bool updatePessoa(const QString& ,const QString& ,const QString& ,const QString&);

    bool getFotos();

    bool getPaginas();

    bool getAlbuns();

    bool getPessoas();

    bool getPessoasByFoto(const QString&);

    bool getAtachments();

    bool deleteFoto(const QString&);

    bool deleteAlbum(const QString&);

    bool deletePagina(const QString&);

    bool deletePessoa(const QString&);

    bool removeAll();

    bool clearAll();

    //bool deleteFromDB();

private:
    QSqlDatabase m_db;
};

#endif // GESTORBD_H
