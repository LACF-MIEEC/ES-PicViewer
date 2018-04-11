#include "pagina.h"

//===============================================================================
//--------------------------------SubClasses------------------------------------
// ------------- VIAGEM ----------------------------

PaginaViagem::PaginaViagem(PageParam atributes):
    Pagina(atributes)
{
    StartDate   =   atributes.StartDate;
    EndDate     =   atributes.EndDate;
}

pageType_t PaginaViagem::getType()
{
    return viagem;
}

QDate PaginaViagem::getStartDate(){
    return StartDate;
}
QDate PaginaViagem::getEndDate(){
    return EndDate;
}

QString PaginaViagem::createFolderName(){
    QString folderName(Path.path());
    folderName.append("/Viagem");
    return folderName;
}
// ------------- FESTA ----------------------------

PaginaFesta::PaginaFesta(PageParam atributes):
    Pagina(atributes)
{
    Date        =   atributes.StartDate;
    PartyType   =   atributes.PartyType;
}

pageType_t PaginaFesta::getType()
{
    return festa;
}

QDate PaginaFesta::getDate(){
    return Date;
}
QString PaginaFesta::getPartyType(){
    return PartyType;
}

QString PaginaFesta::createFolderName(){
    QString folderName(Path.path());
    folderName.append("/Festa");
    return folderName;
}
// ------------- COISA OU PESSOA ----------------------------

PaginaCoisaPessoa::PaginaCoisaPessoa(PageParam atributes):
    Pagina(atributes)
{
}

pageType_t PaginaCoisaPessoa::getType()
{
    return coisaPessoa;
}

QString PaginaCoisaPessoa::createFolderName(){
    QString folderName(Path.path());
    folderName.append("/Coisa");
    return folderName;
}
// ------------- OUTRO ----------------------------

PaginaOutro::PaginaOutro(PageParam atributes):
    Pagina(atributes)
{
    StartDate   =   atributes.StartDate;
    EndDate     =   atributes.EndDate;
}

pageType_t PaginaOutro::getType()
{
    return outro;
}

QDate PaginaOutro::getStartDate(){
    return StartDate;
}
QDate PaginaOutro::getEndDate(){
    return EndDate;
}

QString PaginaOutro::createFolderName(){
    QString folderName(Path.path());
    folderName.append("/Outro");
    return folderName;
}
