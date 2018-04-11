#include "gestorbd.h"


//-------------------------------------------------------------
//CREATE TABLES
//-------------------------------------------------------------
bool GestorBD::createTables()
{
    //********************************************************************************
    //CRIA TABELA FOTO
    //********************************************************************************
    QSqlQuery query;
    query.prepare("CREATE TABLE FOTO("
                  "ID_Foto   INT PRIMARY KEY NOT NULL,"
                  "Path      TEXT,"
                  "ID_Pagina INT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'FOTO': one might already exist.";
        return false;
    }

    //********************************************************************************
    //CRIA TABELA ALBUM
    //********************************************************************************
    query.prepare("CREATE TABLE ALBUM ("
                  "ID_Album    INT PRIMARY KEY NOT NULL,"
                  "Nome_Album  TEXT,"
                  "Path        TEXT,"
                  "Tipo        INT,"
                  "Descricao   TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ALBUM': one might already exist.";
        return false;
    }

    //********************************************************************************
    //CRIA TABELA PAGINA
    //********************************************************************************

    query.prepare("CREATE TABLE PAGINA("
                  "ID_Pagina   INT PRIMARY KEY NOT NULL,"
                  "Tipo        INT ,"
                  "ID_Album    INT ,"
                  "Path        TEXT,"
                  "Data_Inicio TEXT,"
                  "Descricao   TEXT,"
                  "Data_Fim    TEXT,"
                  "Tipo_Festa  TEXT,"


                  "FOREIGN KEY (ID_Album) REFERENCES ALBUM(ID_Album));");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'PAGINA': one might already exist.";
        return false;
    }



    //********************************************************************************
    //CRIA TABELA PESSOA
    //********************************************************************************
    query.prepare("CREATE TABLE PESSOA("
                  "ID_Pessoa   INT PRIMARY KEY NOT NULL,"
                  "Nome_Pessoa TEXT,"
                  "Data_Nasc   TEXT,"
                  "Genero      INT,"
                  "Relacao     TEXT);");



    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'PESSOA': one might already exist.";
        return false;
    }




    //********************************************************************************
    //CRIA TABELA ASSOCIA
    //********************************************************************************
    query.prepare("CREATE TABLE ASSOCIA("
                  "ID_Foto INT,"
                  "ID_Pessoa INT,"
                  "FOREIGN KEY (ID_Foto) REFERENCES FOTO(ID_Foto),"
                  "FOREIGN KEY (ID_Pessoa) REFERENCES Pessoa(Nome));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ASSOCIA': one might already exist.";
        return false;
    }



    return true;
}


//-------------------------------------------------------------
//ADD
//-------------------------------------------------------------
bool GestorBD::addPhoto(Foto *newFoto)
{
    QString Path = newFoto->getPath().path();
    int ID_Foto  = newFoto->getID();
    int ID_Pagina= newFoto->parent()->getID();

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO FOTO (Path, ID_Foto, ID_Pagina) VALUES (:Path,:id_foto,:id_pagina)");
    queryAdd.bindValue(":Path", Path);
    queryAdd.bindValue(":id_foto", ID_Foto);
    queryAdd.bindValue(":id_pagina", ID_Pagina);

    if(!queryAdd.exec())
    {
        qDebug() << "add Foto failed: " << queryAdd.lastError();
        return false;
    }
    return true;
}

bool GestorBD::addAlbum(Album *newAlbum){

    pageType_t Tipo    = newAlbum->getPageType();
    int ID_Album       = newAlbum->getID();
    QString Nome_Album = newAlbum->getName();
    QString Descricao  = newAlbum->getDescription();
    QString Path       = newAlbum->getPath().path();

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO ALBUM (ID_Album, Nome_Album, Path, Tipo, Descricao) VALUES (:id_alb,:nome_alb,:path,:tipo,:desc)");
    queryAdd.bindValue(":id_alb", ID_Album);
    queryAdd.bindValue(":nome_alb", Nome_Album);
    queryAdd.bindValue(":path", Path);
    queryAdd.bindValue(":tipo", Tipo);
    queryAdd.bindValue(":desc", Descricao);

    if(!queryAdd.exec())
    {
        qDebug() << "add Album failed: " << queryAdd.lastError();
        return false;
    }
    return true;
}

bool GestorBD::addPage(Pagina *newPagina){


    int ID_Pagina       = newPagina->getID();
    int ID_Album        = newPagina->parent()->getID();
    pageType_t Tipo            = newPagina->getType();
    QString Descricao   = newPagina->getDescription();
    QString Data_Inicio, Data_Fim,Tipo_Festa;

    if(Tipo==viagem){
        Data_Inicio = newPagina->getStartDate().toString(Qt::ISODate);
        Data_Fim    = newPagina->getEndDate().toString(Qt::ISODate);
        Tipo_Festa  = "NULL";
    }

    if(Tipo==outro){
        Data_Inicio = newPagina->getStartDate().toString(Qt::ISODate);
        Data_Fim    = newPagina->getEndDate().toString(Qt::ISODate);
        Tipo_Festa  = "NULL";
    }

    if(Tipo==coisaPessoa){
        Data_Inicio = "NULL";
        Data_Fim    = "NULL";
        Tipo_Festa  = "NULL";
    }

    if(Tipo==festa){
        Data_Inicio = newPagina->getStartDate().toString(Qt::ISODate);
        Data_Fim    = "NULL";
        Tipo_Festa  = newPagina->getPartyType();
    }


    QString Path = newPagina->getPath().path();



    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO PAGINA (ID_Pagina, ID_Album,Tipo, Descricao,Data_Inicio,Data_Fim,Tipo_Festa,Path) VALUES (:id_pag,:id_alb,:tipo,:desc,:datai,:dataf,:tipof,:path)");
    queryAdd.bindValue(":id_pag", ID_Pagina);
    queryAdd.bindValue(":id_alb", ID_Album);
    queryAdd.bindValue(":tipo", Tipo);
    queryAdd.bindValue(":desc", Descricao);
    queryAdd.bindValue(":datai", Data_Inicio);
    queryAdd.bindValue(":dataf", Data_Fim);
    queryAdd.bindValue(":tipof", Tipo_Festa);
    queryAdd.bindValue(":path", Path);

    if(!queryAdd.exec())
    {
        qDebug() << "add Pagina failed: " << queryAdd.lastError();
        return false;
    }
    return true;
}

bool GestorBD::addPerson(Pessoa *newPessoa){


    int ID_Pessoa       = newPessoa->getID();
    int Genero          = newPessoa->getGender();
    QString Nome_Pessoa = newPessoa->getName();
    QString Data_Nasc   = newPessoa->getBirth().toString();
    QString Relacao     = newPessoa->getBond();

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO PESSOA (ID_Pessoa,Nome_Pessoa, Data_Nasc, Genero, Relacao) VALUES (:id_pessoa,:nome,:data,:gen,:rel)");
    queryAdd.bindValue(":id_pessoa", ID_Pessoa);
    queryAdd.bindValue(":nome", Nome_Pessoa);
    queryAdd.bindValue(":data", Data_Nasc);
    queryAdd.bindValue(":gen", Genero);
    queryAdd.bindValue(":rel", Relacao);

    if(queryAdd.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "add person failed: " << queryAdd.lastError();
        return false;
    }
}


//-------------------------------------------------------------
//UPDATE
//-------------------------------------------------------------
bool GestorBD::updatePhoto(Foto *newFoto){

    QString Path = newFoto->getPath().path();
    int ID_Foto  = newFoto->getID();
    int ID_Pagina= newFoto->parent()->getID();

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE FOTO SET Path = :Path,ID_Pagina = :id_pagina WHERE ID_Foto = :id;");
    queryUpdate.bindValue(":Path", Path);
    queryUpdate.bindValue(":id_pagina", ID_Pagina);
    queryUpdate.bindValue(":id"   , ID_Foto);


    if(!queryUpdate.exec())
    {
        qDebug() << "add person failed: " << queryUpdate.lastError();
        return false;
    }

    return true;
}

bool GestorBD::updateAlbum(Album *newAlbum){

    int Tipo           = newAlbum->getPageType();
    int ID_Album       = newAlbum->getID();
    QString Nome_Album = newAlbum->getName();
    QString Descricao  = newAlbum->getDescription();
    QString Path = newAlbum->getPath().path();

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE ALBUM SET Nome_Album = :nome_alb, Path = :path, Tipo = :tipo, Descricao = :desc WHERE ID_Album = :id_alb; ");
    queryUpdate.bindValue(":id_alb", ID_Album);
    queryUpdate.bindValue(":nome_alb", Nome_Album);
    queryUpdate.bindValue(":path", Path);
    queryUpdate.bindValue(":tipo", Tipo);
    queryUpdate.bindValue(":desc", Descricao);

    if(!queryUpdate.exec())
    {
        qDebug() << "update album failed: " << queryUpdate.lastError();
        return false;
    }

    return true;
}

bool GestorBD::updatePage(Pagina *newPagina){

    int ID_Pagina       = newPagina->getID();
    int ID_Album        = newPagina->parent()->getID();
    int Tipo            = newPagina->getType();
    QString Descricao   = newPagina->getDescription();
    QString Data_Inicio, Data_Fim,Tipo_Festa;

    if(Tipo==viagem){
        Data_Inicio = newPagina->getStartDate().toString();;
        Data_Fim    = newPagina->getEndDate().toString();
        Tipo_Festa  = "NULL";
    }

    if(Tipo==outro){
        Data_Inicio = newPagina->getStartDate().toString();
        Data_Fim    = newPagina->getEndDate().toString();
        Tipo_Festa  = "NULL";
    }

    if(Tipo==coisaPessoa){
        Data_Inicio = "NULL";
        Data_Fim    = "NULL";
        Tipo_Festa  = "NULL";
    }

    if(Tipo==festa){
        Data_Inicio = newPagina->getStartDate().toString();
        Data_Fim    = "NULL";
        Tipo_Festa  = newPagina->getPartyType();
    }

    QString Path = newPagina->getPath().path();

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE PAGINA SET ID_Album = :id_alb, Descricao = :desc, Tipo=:tipo, Data_Inicio=:datai,Data_Fim=:dataf,Tipo_Festa=:tipof,Path=:path WHERE ID_Pagina = :id_pag;");
    queryUpdate.bindValue(":id_pag", ID_Pagina);
    queryUpdate.bindValue(":id_alb", ID_Album);
    queryUpdate.bindValue(":tipo", Tipo);
    queryUpdate.bindValue(":desc", Descricao);
    queryUpdate.bindValue(":datai", Data_Inicio);
    queryUpdate.bindValue(":dataf", Data_Fim);
    queryUpdate.bindValue(":tipof", Tipo_Festa);
    queryUpdate.bindValue(":path", Path);

    if(!queryUpdate.exec())
    {
        qDebug() << "update pagina failed: " << queryUpdate.lastError();
        return false;
    }
    return true;
}

bool GestorBD::updatePerson(Pessoa *newPessoa){


    int ID_Pessoa       = newPessoa->getID();
    int Genero          = newPessoa->getGender();
    QString Nome_Pessoa = newPessoa->getName();
    QString Data_Nasc   = newPessoa->getBirth().toString();
    QString Relacao     = newPessoa->getBond();

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE PESSOA SET Nome_Pessoa = :nome_pessoa,Data_Nasc = :data, Genero = :genero, Relacao = :relacao WHERE ID_Pessoa = :id_pessoa;");
    queryUpdate.bindValue(":id_pessoa"  , ID_Pessoa);
    queryUpdate.bindValue(":genero"     , Genero);
    queryUpdate.bindValue(":data"       , Data_Nasc);
    queryUpdate.bindValue(":nome_pessoa", Nome_Pessoa);
    queryUpdate.bindValue(":relacao"    , Relacao);

    if(!queryUpdate.exec())
    {
        qDebug() << "update pessoa failed: " << queryUpdate.lastError();
        return false;
    }
    return true;
}


//-------------------------------------------------------------
//GET
//-------------------------------------------------------------
QVector<PhotoParam*> GestorBD::getPhotos(Pagina* Page){

    int PageID = Page->getID();

    QSqlQuery queryGet;
    queryGet.prepare("SELECT * FROM FOTO WHERE ID_Pagina=:id_pag;");
    queryGet.bindValue(":id_pag", PageID);

    if(!queryGet.exec())
    {
        qDebug() << "get foto failed: " << queryGet.lastError();
    }

    QVector<PhotoParam*> Fotos;

    PhotoParam *Atributes;

    while(queryGet.next())
    {
        Atributes           = new PhotoParam;
        Atributes->Parent    = Page;
        Atributes->Gestor    = this;
        Atributes->ID        = queryGet.value("ID_Foto").toInt();
        Atributes->Path.setPath(queryGet.value("Path").toString());

        Fotos.append(Atributes);

    }
    return Fotos;
}

QVector<PageParam*> GestorBD::getPages(Album* Alb){

    int AlbumID = Alb->getID();

    QSqlQuery queryGet;

    queryGet.prepare("SELECT * FROM PAGINA WHERE ID_Album = id_album;");
    queryGet.bindValue(":id_album", AlbumID);
    if(!queryGet.exec())
    {
        qDebug() << "get pagina failed: " << queryGet.lastError();
    }


    QVector<PageParam*> Paginas;
    PageParam *Atributes;
    pageType_t Type;

    while(queryGet.next())
    {
        Atributes               = new PageParam;
        Atributes->Gestor        = this;
        Atributes->Parent        = Alb;
        Atributes->ID            = queryGet.value("ID_Pagina").toInt();
        Atributes->Description   = queryGet.value("Descricao").toString();
        Type                    = (pageType_t)queryGet.value("Tipo").toInt();
        Atributes->Path.setPath(queryGet.value("Path").toString());
        Atributes->StartDate     = queryGet.value("DataInicio").toDate();
        Atributes->EndDate       = queryGet.value("DataFim").toDate();
        Atributes->PartyType     = queryGet.value("Tipo_Festa").toString();

        switch(Type){
        case viagem:
            Paginas.append(Atributes);
            break;
        case coisaPessoa:
            Paginas.append(Atributes);
            break;
        case festa:
            Paginas.append(Atributes);
            break;
        case outro:
            Paginas.append(Atributes);
            break;
        }
    }
    return Paginas;
}

QVector<PersonParam*> GestorBD::getPeople(ListaPessoas* People){

    QSqlQuery queryGet;
    queryGet.prepare("SELECT * FROM PESSOA;");
    if(!queryGet.exec())
    {
        qDebug() << "get pessoa failed: " << queryGet.lastError();
    }


    QVector<PersonParam*> Pessoas;

    PersonParam *Atributes;


    while(queryGet.next()){
        Atributes           = new PersonParam;
        Atributes->Gestor    = this;
        Atributes->Parent    = People;
        Atributes->ID        = queryGet.value("ID_Pessoa").toInt();
        Atributes->Name      = queryGet.value("Nome_Pessoa").toString();
        Atributes->Birth     = queryGet.value("Data_Nasc").toDate();
        Atributes->Gender    = (gender)queryGet.value("Genero").toInt();
        Atributes->Bond      = queryGet.value("Relacao").toString();

        Pessoas.append(Atributes);
    }
    return Pessoas;
}

QVector<AlbumParam*> GestorBD::getAlbums(ListaAlbuns* Albs){

    QSqlQuery query;
    query.prepare("SELECT * FROM ALBUM;");
    if(!query.exec())
    {
        qDebug() << "get album failed: " << query.lastError();
    }


    QVector<AlbumParam*> Albums;

    AlbumParam *Atributes;

    while(query.next()){

        Atributes                =   new AlbumParam;
        Atributes->Gestor        =   this;
        Atributes->Parent        =   Albs;
        Atributes->ID            =   query.value("ID_Album").toInt();
        Atributes->Name          =   query.value("Nome_Album").toString();
        Atributes->PageType      =   (pageType_t)query.value("Tipo").toInt();
        Atributes->Description   =   query.value("Descricao").toString();
        Atributes->Path.setPath(query.value("Path").toString());

        Albums.append(Atributes);
        //Albuns.append(new Album(atributes));
    }
    return Albums;
}


//-------------------------------------------------------------
//DELETE
//-------------------------------------------------------------
bool GestorBD::deletePhoto(Foto *delFoto){

    int ID_Foto  = delFoto->getID();

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM FOTO WHERE ID_Foto=:id;");
    queryDel.bindValue(":id", ID_Foto);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }

    queryDel.prepare("DELETE FROM ASSOCIA WHERE ID_Foto=:id;");
    queryDel.bindValue(":id", ID_Foto);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool GestorBD::deletePage(Pagina *delPagina){

    int ID_Pagina  = delPagina->getID();

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM PAGINA WHERE ID_Pagina=:id;");
    queryDel.bindValue(":id", ID_Pagina);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool GestorBD::deletePerson(Pessoa *delPessoa){

    int ID_Pessoa  = delPessoa->getID();

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM PESSOA WHERE ID_Pessoa=:id_pessoa;");
    queryDel.bindValue(":id_pessoa", ID_Pessoa);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }

    queryDel.prepare("DELETE FROM ASSOCIA WHERE ID_Pessoa=:id_pessoa;");
    queryDel.bindValue(":id_pessoa", ID_Pessoa);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool GestorBD::deleteAlbum(Album *delAlbum){

    int ID_Album  = delAlbum->getID();

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM ALBUM WHERE ID_Album=:id;");
    queryDel.bindValue(":id", ID_Album);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }

    return true;
}


//-------------------------------------------------------------
//OTHERS
//-------------------------------------------------------------
bool GestorBD::removeAll(){

    QSqlQuery queryRem;
    queryRem.prepare("DROP TABLE FOTO;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }

    queryRem.prepare("DROP TABLE ASSOCIA;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }


    queryRem.prepare("DROP TABLE PAGINA;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }


    queryRem.prepare("DROP TABLE PESSOA;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }


    queryRem.prepare("DROP TABLE ALBUM;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }
    return true;
}

bool GestorBD::clearAll(){

    QSqlQuery queryClr;
    queryClr.prepare("DELETE FROM FOTO;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear Table failed: " << queryClr.lastError();
        return false;
    }

    queryClr.prepare("DELETE FROM ASSOCIA;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear Table failed: " << queryClr.lastError();
        return false;
    }


    queryClr.prepare("DELETE FROM PAGINA;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear Table failed: " << queryClr.lastError();
        return false;
    }


    queryClr.prepare("DELETE FROM PESSOA;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear Table failed: " << queryClr.lastError();
        return false;
    }


    queryClr.prepare("DELETE FROM ALBUM;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear Table failed: " << queryClr.lastError();
        return false;
    }
    return true;
}

GestorBD::GestorBD(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

GestorBD::~GestorBD()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool GestorBD::isOpen() const
{
    return m_db.isOpen();
}

/*
bool GestorBD::getPessoasByFoto(const QString& Foto_ID){

    QSqlQuery query;
    query.prepare("SELECT Nome_Pessoa,Data_Nasc,Genero, Relacao FROM ASSOCIA NATURAL JOIN PESSOA WHERE ID_Foto=  :id;");
    query.bindValue(":id", Foto_ID);
    if(!query.exec())
    {
        qDebug() << "get pessoa failed: " << query.lastError();
        return false;
    }
    while (query.next())
    {
        qDebug() << query.value("Nome_Pessoa").toString() << " " << query.value("Data_Nasc").toString()
                 << " " << query.value("Genero").toString() << " " << query.value("Relacao").toString();
        qDebug();
    }
    return true;
}
bool GestorBD::addAtachment(const QString& ID_Foto,const QString& Nome_Pessoa)
{

    QVector<Pessoa*> People= newFoto->getPeople();
    Pessoa *Person;
    int ID_Pessoa;

    for(int i=0; i<People.size();i++){
        Person=People.at(i);
        ID_Pessoa=Person->getID();

    }

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO ASSOCIA (ID_Foto, Nome_Pessoa) VALUES (:id,:nome_pessoa);");
    queryAdd.bindValue(":id", ID_Foto);
    queryAdd.bindValue(":nome_pessoa", Nome_Pessoa);

    if(!queryAdd.exec())
    {
        qDebug() << "add Atachment failed: " << queryAdd.lastError();
        return false;
    }

    return true;
}

bool GestorBD::getAtachments(){

    QSqlQuery query;
    query.prepare("SELECT * FROM ASSOCIA;");
    if(!query.exec())
    {
        qDebug() << "get pessoa failed: " << query.lastError();
        return false;
    }
    while (query.next())
    {
        qDebug() << query.value("ID_Foto").toString() << " " << query.value("Nome_Pessoa").toString();
        qDebug();
    }
    return true;
}
*/

