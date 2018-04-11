#include "pagina.h"

Pagina::Pagina(int id, QString desc, QDir path, Album* parent=0,GestorBD* gestor = 0)
{
    ID=id;
    Description=desc;
    Path=path;
    Parent=parent;
    oGestor=gestor;
}
int Pagina::deleteSelf(){

}

int Pagina::getID(){
    return ID;
}

QString Pagina::getDescription(){
    return Description
}

QDir Pagina::getPath(){
    return Path;
}

QVector<Foto*> Pagina::getPhotos(){
    return Photos;
}

Album* Pagina::parent(){
    return Parent;
}


int Pagina::acceptPhoto(Foto* photo){
    return -1;
}

int createFolder(QString folderName){
    return -1;
}
// ------------- VIAGEM ----------------------------

PaginaViagem::PaginaViagem(int id, QString desc, QDir path, QDateTime start, QDateTime end, Album* parent=0,GestorBD* gestor = 0):
    Pagina(id,desc,path,parent,gestor)
{
    StartDate=start;
    EndDate=end;
}

pageType_t PaginaViagem::getType()
{
    return viagem;
}

QString PaginaViagem::createFolderName(){
    QStringRef folderName = "Viagem";
    return folderName;
}
// ------------- FESTA ----------------------------

PaginaFesta::PaginaFesta(int id, QString desc, QDir path, QDateTime date, QString type, Album* parent=0,GestorBD* gestor = 0):
    Pagina(id,desc,path,parent,gestor)
{
    Date=date;
    PartyType=type;
}
pageType_t PaginaFesta::getType()
{
    return festa;
}

QString PaginaFesta::createFolderName(){
    QStringRef folderName = "Festa";
    return folderName;
}
// ------------- COISA OU PESSOA ----------------------------

PaginaCoisaPessoa::PaginaCoisaPessoa(int id, QString desc, QDir path, Album* parent=0,GestorBD* gestor = 0):
    Pagina(id,desc,path,parent,gestor)
{
}
pageType_t PaginaCoisaPessoa::getType()
{
    return coisaPessoa;
}

QString PaginaCoisaPessoa::createFolderName(){
    QStringRef folderName = "Coisa";
    return folderName;
}
// ------------- OUTRO ----------------------------

PaginaOutro::PaginaOutro(int id, QString desc, QDir path, QDateTime start, QDateTime end, Album* parent=0,GestorBD* gestor = 0):
    Pagina(id,desc,path,parent,gestor)
{
    StartDate=start;
    EndDate=end;
}

pageType_t PaginaOutro::getType()
{
    return outro;
}

QString PaginaOutro::createFolderName(){
    QStringRef folderName = "Outro";
    return folderName;
}
