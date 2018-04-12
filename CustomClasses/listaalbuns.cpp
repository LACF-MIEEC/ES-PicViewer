#include "listaalbuns.h"


ListaAlbuns::ListaAlbuns(GestorBD *gestor)
{
    qDebug() << "Entered constructor";
    allocatedAlbumID.fill(0);
    allocatedAlbumID.insert(allocatedAlbumID.size(), 10, 0);

    maxAlbumID = 0;

    qDebug() << "vector size is " << allocatedAlbumID.size() << ", maxID is " << maxAlbumID;

    oGestor = gestor;

    Albums = new QVector<Album*>();
    QVector<AlbumParam*> *AlbumAtributes = oGestor->getAlbums(this);
    for(int i=0;AlbumAtributes->size();i++){
        Albums->append(new Album(*AlbumAtributes->at(i)));
    }
    delete AlbumAtributes;

}
ListaAlbuns::~ListaAlbuns(){
    for(int i=0;Albums->size();i++){
        Albums->at(i)->deleteSelf();
    }
    delete this;
}


//------------------Private-------------------//
int ListaAlbuns::generateID(QVector<int> &allocatedID, int &maxID)
{
    qDebug() << "Hello World";
    for (int index = 0; index < allocatedID.size(); index++ )
    {
        if (allocatedID.at(index) == 0)
        {
            qDebug() << "Free space found: index = " << index << ", vector[index] = " << allocatedID.at(index);

            allocatedID[index] = 1;
            qDebug() << ", vector[index] is now " << allocatedID.at(index);;

            return index;
        }
        if (index == maxID){
            qDebug() << "Incrementing maxID";
            maxID += 1;
            if (maxID == allocatedID.size())
            {
                qDebug() << "Allocating more space";
                allocatedID.insert(allocatedID.size(), 10, 0);
            }
            allocatedID[maxID] = 1;
            return maxID;
        }
    }
    // Program shouldn't get here...
    qDebug() << "Are you sure the program is correct?";
    // Are we here? vector is full, we need to append new values
    if (allocatedID.size() == maxID+1){
        qDebug() << "Incrementing maxID and allocating more space";
        allocatedID.insert(allocatedID.size(), 10, 0);
        maxID += 1;
        //allocatedID.append(1);
        allocatedID[maxID] = 1;
        return maxID;
        //return maxID;
    }
    // If the program gets here, something went wrong
    qDebug() << "Something went wrong generating an ID";
    qDebug() << "MaxID = " << maxID << ", vector size = " << allocatedID.size();
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
