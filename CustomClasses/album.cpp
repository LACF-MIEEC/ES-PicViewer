#include "album.h"
#include "gestorbd.h"

Album::Album(AlbumParam atributes)
{
    ID          =   atributes.ID;
    Name        =   atributes.Name;
    Description =   atributes.Description;
    Path        =   atributes.Path;
    PageType    =   atributes.PageType;
    Parent      =   atributes.Parent;
    oGestor     =   atributes.Gestor;

    Pages.clear();

    if(RunMode.testFlag(Setup::Boot)){
        QVector<PageParam*> PageAtributes = oGestor->getPages(atributes);
        for(int i=0;PageAtributes.size();i++){
            switch(PageType)
            case viagem:
                Pages.append(new PaginaViagem(PageAtributes[i]));
                break;
            case coisaPessoa:
                Pages.append(new PaginaCoisaPessoa(PageAtributes[i]));
                break;
            case festa:
                Pages.append(new PaginaFesta(PageAtributes[i]));
                break;
            case outro:
                Pages.append(new PaginaOutro(PageAtributes[i]));
                break;
        }
        RunMode = Setup::RunTime;
    }
    if(RunMode.testFlag(Setup::RunTime)){
        if(!oGestor->addAlbum(atributes))
            qDebug() << "Unable to Save Album";
        qDebug() << "Album Saved";
    }
}

//----------------Get Atributes----------------//
void Album::deleteSelf(){
    for(int i=0;Pages.size();i++){
        Pages.at(i)->deleteSelf();
    }

    delete this;
}

int Album::getID(){
    return ID;
}
QString Album::getName(){
    return Name;
}
QString Album::getDescription(){
    return Description;
}
QDir Album::getPath(){
    return Path;
}
pageType_t Album::getPageType(){
    return PageType;
}

QVector<Pagina*> Album::getPages(){
    return Pages;
}

ListaAlbuns* Album::parent(){
    return Parent;
}

//-------------------Create--------------------//

Pagina* Album::createPage(PageParam atributes){

    Pagina* newPage;

    switch(PageType){
    case viagem:
        newPage=new PaginaViagem(atributes);
        Pages.append(newPage);
        return newPage;
    case festa:
        newPage=new PaginaFesta(atributes);
        Pages.append(newPage);
        return newPage;
    case coisaPessoa:
        newPage=new PaginaCoisaPessoa(atributes);
        Pages.append(newPage);
        return newPage;
    case outro:
        newPage=new PaginaOutro(atributes);
        Pages.append(newPage);
        return newPage;
    default:
        return NULL;
    }
}

Foto* Album::createPhoto(PhotoParam atributes, Pagina* destination){
    return destination->createPhoto(atributes);
}

int Album::createFolder(QString folderName){
    QDir folder(folderName);
    QString newFolderName;

    for(int i=1;folder.exists();i++){
        newFolderName.clear();
        newFolderName = folderName;
        newFolderName.append("(");
        newFolderName.append(i);
        newFolderName.append(")");
    }
    if(folder.mkdir(newFolderName))
        return 0;
    return -1;
}
QString Album::createFolderName(){
    QString folderName(Path.path());
    folderName.append("/Album");
    return folderName;
}
