#include "listaalbuns.h"


ListaAlbuns::ListaAlbuns(GestorBD *gestor)
{
    qDebug() << "ListaAlbuns: Initializing AlbumID.";
    allocatedAlbumID.clear();
    allocatedAlbumID.insert(allocatedAlbumID.size(), 10, 0);
    allocatedAlbumID.replace(0, 1);
    maxAlbumID = 0;
    qDebug() << "ListaAlbuns: allocatedAlbumID size is " << allocatedAlbumID.size() << ", maxAlbumID is " << maxAlbumID;

    qDebug() << "ListaAlbuns: Initializing PageID.";
    allocatedPageID.clear();
    allocatedPageID.insert(allocatedPageID.size(), 10, 0);
    allocatedPageID.replace(0, 1);
    maxPageID = 0;
    qDebug() << "ListaAlbuns: allocatedPageID size is " << allocatedPageID.size() << ", maxPageID is " << maxPageID;

    qDebug() << "ListaAlbuns: Initializing PhotoID.";
    allocatedPhotoID.clear();
    allocatedPhotoID.insert(allocatedPhotoID.size(), 10, 0);
    allocatedPhotoID.replace(0, 1);
    maxPhotoID = 0;
    qDebug() << "ListaAlbuns: allocatedPhotoID size is " << allocatedPhotoID.size() << ", maxPhotoID is " << maxPhotoID;

    oGestor = gestor;
    Albums = new QVector<Album*>();
}
ListaAlbuns::~ListaAlbuns(){
    for(int i=0;i<Albums->size();i++){
        delete Albums->at(i);
    }
    delete Albums;
}

bool ListaAlbuns::loadAlbuns(GestorBD *gestor){
    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "ListaAlbuns.load():ERROR GestorBD not set.";
        return false;
    }

    QVector<AlbumParam*> *AlbumAtributes = gestor->getAlbums(this);
    if(!AlbumAtributes){
        qDebug() << "ListaAlbuns.load(): ERROR GestorBD->Fail to load.";
        delete AlbumAtributes;
        return false;
    }

    Albums->clear();
    for(int i=0;i<AlbumAtributes->size();i++){
        if(!AlbumAtributes->at(i)->Path.exists()){
            qDebug() << "ListaAlbuns.load(): ERROR No Path to Album. Possible unauthorized deletion";
            for(int i=0; i<Albums->size();i++){
                delete Albums->at(i);
            }
            Albums->clear();
            delete AlbumAtributes;
            return false;
        }
        Albums->append(new Album(*AlbumAtributes->at(i)));
    }
    delete AlbumAtributes;

    return true;
}

bool ListaAlbuns::loadAll(GestorBD* gestor){
    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "ListaAlbuns.loadAll():ERROR GestorBD not set.";
        return false;
    }

    if(!loadAlbuns(gestor)){
        qDebug() << "ListaAlbuns.loadAll():ERROR loadAlbums().";
    }

    for(int i=0;i<Albums->size();i++){
        if(!Albums->at(i)->loadPages(gestor)){
            qDebug() << "ListaAlbuns.loadAll():ERROR loadPages().";
        }
    }
    for(int i=0;i<Albums->size();i++){
        for(int j=0;j<Albums->at(i)->getPages()->size();j++){
            if(!Albums->at(i)->getPages()->at(j)->loadPhotos(gestor)){
                qDebug() << "ListaAlbuns.loadAll():ERROR loadPhotos().";
            }
        }
    }


    return true;
}
//------------------Private-------------------//
int ListaAlbuns::generateID(QVector<int> &allocatedID, int &maxID)
{
    for (int index = 0; index < allocatedID.size(); index++ )
    {
        if (allocatedID.at(index) == 0)
        {
            qDebug() << "ListaAlbuns::generateID() ->Free ID found " << index << ", Vector[index] = " << allocatedID.at(index);
            allocatedID.replace(index,1);
            qDebug() << "ListaAlbuns::generateID() ->Vector[index] replaced by" << allocatedID.at(index);;
            return index;
        }
        if (index == maxID){
            qDebug() << "ListaAlbuns::generateID() -> Incrementing maxID.";
            maxID += 1;
            if (maxID == allocatedID.size())
            {
                qDebug() << "ListaAlbuns::generateID() -> Vector full Allocating more space.";
                allocatedID.insert(allocatedID.size(), 10, 0);
            }
            allocatedID.replace(maxID,1);
            return maxID;
        }
    }
    //This Should't happen!!
    if (allocatedID.size() == maxID+1){
        qDebug() << "ListaAlbuns::generateID() -> Index Problem: Allocating more space";
        allocatedID.insert(allocatedID.size(), 10, 0);
        maxID += 1;
        allocatedID.replace(maxID,1);
        return maxID;
    }
    qDebug() << "ListaAlbuns: Something went wrong generating an ID";
    qDebug() << "ListaAlbuns: MaxID = " << maxID << ", vector size = " << allocatedID.size();
    return -1;


}

int ListaAlbuns::genAlbumID(){
    return generateID(allocatedAlbumID, maxAlbumID);
}

int ListaAlbuns::genPageID(){
    return generateID(allocatedPageID, maxPageID);
}

int ListaAlbuns::genPhotoID(){
    return generateID(allocatedPhotoID, maxPhotoID);
}

//----------------GetAtributes----------------//

QVector<Album*>* ListaAlbuns::getAlbums(){
    return Albums;
}

//------------------Create--------------------//
Album* ListaAlbuns::createAlbum(AlbumParam atributes){
    atributes.ID=genAlbumID();
    Album* newAlbum = new Album(atributes);

    if(!newAlbum->createFolder()){
        allocatedAlbumID.replace(atributes.ID,0);
        delete newAlbum;
        return nullptr;
    }
    atributes.Path.setPath(newAlbum->getPath().path());
    if(!oGestor->addAlbum(&atributes)){
        delete newAlbum;
        QDir MainPath(newAlbum->getPath());
        MainPath.cdUp();
        if(MainPath.rmdir(newAlbum->getPath().dirName())){
            //BIG PROBLEM
            qDebug() << "ListaAlbuma::createAlbum()->ERROR Removing Folder:" << newAlbum->getPath().dirName();
            return nullptr;
        }
        return nullptr;
    }

        Albums->append(newAlbum);
        return newAlbum;

}

Pagina* ListaAlbuns::createPage(PageParam atributes, Album* destination){
    atributes.ID=genPageID();
    return destination->createPage(atributes);
}

Foto* ListaAlbuns::createPhoto(PhotoParam atributes, Pagina* destPage, Album* destAlbum){
    atributes.ID=genPhotoID();
    return destAlbum->createPhoto(atributes,destPage);
}
