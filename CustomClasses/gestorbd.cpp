#include "gestorbd.h"


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

bool GestorBD::createTables()
{
    //********************************************************************************
    //CRIA TABELA FOTO
    //********************************************************************************
    QSqlQuery query;
    query.prepare("CREATE TABLE FOTO("
                  "ID_Foto INT PRIMARY KEY NOT NULL,"
                  "Path VARCHAR (50),"
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
                  "ID_Album INT PRIMARY KEY NOT NULL,"
                  "Nome_Album VARCHAR(25),"
                  "Diretoria VARCHAR(100),"
                  "Tipo VARCHAR(20),"
                  "Descricao VARCHAR(100));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ALBUM': one might already exist.";
        return false;
    }

    //********************************************************************************
    //CRIA TABELA PAGINA
    //********************************************************************************

    query.prepare("CREATE TABLE PAGINA("
                  "ID_Pagina INT PRIMARY KEY NOT NULL,"
                  "Descricao VARCHAR(50),"
                  "ID_Album INT,"
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
                  "Nome_Pessoa VARCHAR(25) PRIMARY KEY NOT NULL,"
                  "Data_Nasc VARCHAR(20),"
                  "Genero VARCHAR(20),"
                  "Relacao VARCHAR(20));");



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
                  "Nome_Pessoa VARCHAR(25),"
                  "FOREIGN KEY (ID_Foto) REFERENCES FOTO(ID_Foto),"
                  "FOREIGN KEY (Nome_Pessoa) REFERENCES Pessoa(Nome));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ASSOCIA': one might already exist.";
        return false;
    }



    return true;
}

bool GestorBD::addFoto(Foto *newFoto)
{
        QString Path = newFoto->getPath();
        int ID_Foto  = newFoto->getID();
        int ID_Pagina= newFoto->parent()->getID();

        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO FOTO (Path, ID_Foto, ID_Pagina) VALUES (:Path,:id,:id_pagina)");
        queryAdd.bindValue(":Path", Path);
        queryAdd.bindValue(":id", ID_Foto);
        queryAdd.bindValue(":id_pagina", ID_Pagina);

        if(!queryAdd.exec())
        {
            qDebug() << "add Foto failed: " << queryAdd.lastError();
            return false;
        }


        /*
        Função deve receber como parametro uma tabela de pessoas que estão associadas à foto e
        inserir na tabela tantas linhas quantas pessoas houver

        for(){
            addAtachment
        }*/
        return true;
}

bool GestorBD::addAtachment(const QString& ID_Foto,const QString& Nome_Pessoa)
{
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

bool GestorBD::addAlbum(const QString& ID_Album,const QString& Nome_Album,const QString& Diretoria,const QString& Tipo,const QString& Descricao){

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO ALBUM (ID_Album, Nome_Album, Diretoria, Tipo, Descricao) VALUES (:id_alb,:nome_alb,:direct,:tipo,:desc)");
    queryAdd.bindValue(":id_alb", ID_Album);
    queryAdd.bindValue(":nome_alb", Nome_Album);
    queryAdd.bindValue(":direct", Diretoria);
    queryAdd.bindValue(":tipo", Tipo);
    queryAdd.bindValue(":desc", Descricao);

    if(!queryAdd.exec())
    {
        qDebug() << "add Album failed: " << queryAdd.lastError();
        return false;
    }
   return true;
}

bool GestorBD::addPagina(const QString& ID_Pagina,const QString& ID_Album,const QString& Descricao){

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO PAGINA (ID_Pagina, ID_Album, Descricao) VALUES (:id_pag,:id_alb,:desc)");
    queryAdd.bindValue(":id_pag", ID_Pagina);
    queryAdd.bindValue(":id_alb", ID_Album);
    queryAdd.bindValue(":desc", Descricao);
    if(!queryAdd.exec())
    {
        qDebug() << "add Pagina failed: " << queryAdd.lastError();
        return false;
    }
    return true;
}

bool GestorBD::addPessoa(const QString& Nome,const QString& Data_Nasc,const QString& Genero,const QString& Relacao){


    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO PESSOA (Nome_Pessoa, Data_Nasc, Genero, Relacao) VALUES (:nome,:data,:gen,:rel)");
    queryAdd.bindValue(":nome", Nome);
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

bool GestorBD::updateFoto(const QString& ID_Foto,const QString& Path,const QString& data,const QString& id_pagina){


        QSqlQuery queryUpdate;
        queryUpdate.prepare("UPDATE FOTO SET Path = :Path,ID_Pagina = :id_pagina WHERE ID_Foto = :id;");
        queryUpdate.bindValue(":Path", Path);
        queryUpdate.bindValue(":id_pagina", id_pagina);
        queryUpdate.bindValue(":id"   , ID_Foto);


        if(!queryUpdate.exec())
        {
            qDebug() << "add person failed: " << queryUpdate.lastError();
            return false;
        }


        /*
        Função deve receber como parametro uma tabela de pessoas que estão associadas à foto e
        inserir na tabela tantas linhas quantas pessoas houver

        for(){

        }*/
        return true;
}

bool GestorBD::updateAlbum(const QString& ID_Album,const QString& Nome_Album,const QString& Diretoria,const QString& Tipo,const QString& Descricao){

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE ALBUM SET Nome_Album = :nome, Diretoria = :dir, Tipo = :tipo, Descricao = :desc WHERE ID_Album = :id; ");
    queryUpdate.bindValue(":nome", Nome_Album);
    queryUpdate.bindValue(":dir", Diretoria);
    queryUpdate.bindValue(":tipo", Tipo);
    queryUpdate.bindValue(":desc", Descricao);
    queryUpdate.bindValue(":id", ID_Album);

    if(!queryUpdate.exec())
    {
        qDebug() << "update album failed: " << queryUpdate.lastError();
        return false;
    }

    return true;
}

bool GestorBD::updatePagina(const QString& ID_Pagina,const QString& ID_Album,const QString& Descricao){

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE PAGINA SET ID_Album = :id_alb, Descricao = :desc WHERE ID_Pagina = :id;");
    queryUpdate.bindValue(":id_alb", ID_Album);
    queryUpdate.bindValue(":desc" , Descricao);
    queryUpdate.bindValue(":id"   , ID_Pagina);

    if(!queryUpdate.exec())
    {
        qDebug() << "update pagina failed: " << queryUpdate.lastError();
        return false;
    }
    return true;
}

bool GestorBD::updatePessoa(const QString& Nome,const QString& Data_Nasc,const QString& Genero,const QString& Relacao){


    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE PESSOA SET Data_Nasc = :data, Genero = :genero, Relacao = :relacao WHERE Nome_Pessoa = :nome;");
    queryUpdate.bindValue(":genero", Genero);
    queryUpdate.bindValue(":data" , Data_Nasc);
    queryUpdate.bindValue(":nome"   , Nome);
    queryUpdate.bindValue(":relacao", Relacao);

    if(!queryUpdate.exec())
    {
        qDebug() << "update pessoa failed: " << queryUpdate.lastError();
        return false;
    }
    return true;
}

bool GestorBD::getFotos(){

    QSqlQuery query;
    query.prepare("SELECT * FROM FOTO;");
    if(!query.exec())
    {
        qDebug() << "get foto failed: " << query.lastError();
        return false;
    }
    while (query.next())
    {
        qDebug() << query.value("ID_Foto").toString()      << " " << query.value("ID_Pagina").toString()
                 << " " << query.value("Path").toString();
        qDebug();
    }
    return true;
}

bool GestorBD::getPaginas(){

    QSqlQuery query;
    query.prepare("SELECT * FROM PAGINA;");
    if(!query.exec())
    {
        qDebug() << "get pagina failed: " << query.lastError();
        return false;
    }
    while (query.next())
    {
        qDebug() << query.value("ID_Pagina").toString() << " " << query.value("ID_Album").toString()
                 << " " << query.value("Descricao").toString();
        qDebug();
    }
    return true;
}

bool GestorBD::getPessoas(){

   QSqlQuery query;
   query.prepare("SELECT * FROM PESSOA;");
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

bool GestorBD::getAlbuns(){

   QSqlQuery query;
   query.prepare("SELECT * FROM ALBUM;");
   if(!query.exec())
   {
       qDebug() << "get album failed: " << query.lastError();
       return false;
   }
    while (query.next())
    {
        qDebug() << query.value("ID_Album").toString()  << " " << query.value("Nome_Album").toString()
                 << query.value("Diretoria").toString() << " " << query.value("Tipo").toString()
                 << " " << query.value("Descricao").toString();
        qDebug();
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

bool GestorBD::deleteFoto(const QString& ID_Foto){
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

bool GestorBD::deletePagina(const QString& ID_Pagina){
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

bool GestorBD::deletePessoa(const QString& Nome_Pessoa){

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM PESSOA WHERE Nome_Pessoa=:nome;");
    queryDel.bindValue(":nome", Nome_Pessoa);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }

    queryDel.prepare("DELETE FROM ASSOCIA WHERE Nome_Pessoa=:nome;");
    queryDel.bindValue(":nome", Nome_Pessoa);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool GestorBD::deleteAlbum(const QString& ID_Album){

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
/*
bool DB_Manager::deleteFromDB(){
QSqlQuery queryRem;
queryRem.prepare("DROP TABLE FOTO;");

if(!queryRem.exec())
{
    qDebug() << "Drop Table failed: " << queryRem.lastError();
    return false;
}

}
*/
