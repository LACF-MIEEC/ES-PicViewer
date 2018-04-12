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

    if(RunMode.testFlag(Setup::Boot)){

}

bool Album::load(GestorBD *gestor=0){
    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "Album.load():ERROR GestorBD not set.";
        return false;
    }

    Pages = new QVector<Pagina*>();
    QVector<PageParam*> *PageAtributes = oGestor->getPages(&atributes);
    for(int i=0;i<PageAtributes->size();i++){
        PageAtributes->at(i)->Parent=this;
        switch(PageType){
        case viagem:
            Pages->append(new PaginaViagem(*PageAtributes->at(i)));
            break;
        case coisaPessoa:
            Pages->append(new PaginaCoisaPessoa(*PageAtributes->at(i)));
            break;
        case festa:
            Pages->append(new PaginaFesta(*PageAtributes->at(i)));
            break;
        case outro:
            Pages->append(new PaginaOutro(*PageAtributes->at(i)));
            break;
        }
    }
    delete PageAtributes;
}

//----------------Get Atributes----------------//
void Album::deleteSelf(){
    for(int i=0;Pages->size();i++){
        Pages->at(i)->deleteSelf();
    }
    delete Pages;
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

QVector<Pagina*>* Album::getPages(){
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
        break;
    case festa:
        newPage=new PaginaFesta(atributes);
        break;
    case coisaPessoa:
        newPage=new PaginaCoisaPessoa(atributes);
        break;
    case outro:
        newPage=new PaginaOutro(atributes);
        break;
    default:
        return nullptr;
    }
    if(!oGestor->addPage(&atributes)){
        qDebug() << "Unable to Save Page";
        delete newPage;
        return nullptr;
    }
    else{
        qDebug() << "Page Saved";
        Pages->append(newPage);
        return newPage;
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
