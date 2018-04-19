
#include "gestorbd.h"
#include "foto.h"
#include "pagina.h"
#include "album.h"
#include "listaalbuns.h"
#include "listapessoas.h"
#include "pessoa.h"


Pagina::Pagina(PageParam atributes)
{
    ID          =   atributes.ID;
    Description =   atributes.Description;
    Path        =   atributes.Path;
    Parent      =   atributes.Parent;
    oGestor     =   atributes.Gestor;

    Photos = new QVector<Foto*>();
}
Pagina::~Pagina(){
    for(int i=0;i<Photos->size();i++){
        delete Photos->at(i);
    }
    delete Photos;
}

bool Pagina::loadPhotos(QVector<int> &allocatedID, int &maxID,GestorBD* gestor){
    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "Pagina.load():ERROR GestorBD not set.";
        return false;
    }
    PageParam atributes;
    atributes.ID=ID;
    QVector<PhotoParam*> *PhotoAtributes = gestor->getPhotos(&atributes);
    if(!PhotoAtributes){
        qDebug() << "Pagina.load(): ERROR GestorBD->Fail to load.";
        delete PhotoAtributes;
        return false;
    }

    Photos->clear();
    for(int i=0;i<PhotoAtributes->size();i++){
        if(!PhotoAtributes->at(i)->Path.exists(PhotoAtributes->at(i)->Path.path())){
            qDebug() << "Pagina.load(): ERROR No Path to Photo. Possible unauthorized deletion";
            for(int i=0; i<Photos->size();i++){
                delete Photos->at(i);
            }
            Photos->clear();
            delete PhotoAtributes;
            return false;
        }
        PhotoAtributes->at(i)->Parent=this;
        Photos->append(new Foto(*PhotoAtributes->at(i)));
    }
    delete PhotoAtributes;

    int AllocSize;
    int CurrentID;

    //Inicializar PageID
    for(int i=0;i<Photos->size();i++){

        AllocSize=allocatedID.size();
        CurrentID=Photos->at(i)->getID();

        if(CurrentID > AllocSize){
            allocatedID.insert(AllocSize, CurrentID-AllocSize+1, 0);
        }
        allocatedID.replace(CurrentID,1);
        if(maxID<CurrentID)
            maxID=CurrentID;

    }

    return true;

}
//------------------Get Atributes--------------------//

int Pagina::getID(){
    return ID;
}

QString Pagina::getDescription(){
    return Description;
}

QDir Pagina::getPath(){
    return Path;
}

QVector<Foto *> Pagina::getPhotos(){
    return Photos;
}

Album* Pagina::parent(){
    return Parent;
}

//-------------------Create--------------------------//

Foto* Pagina::createPhoto(PhotoParam atributes){

    if(!atributes.Path.exists(atributes.Path.path())){
        qDebug() << "Pagina::createPhoto->ERROR File"<< atributes.Path.path() << "doesn't exist!!";
        return nullptr;
    }
    QString oldPhotoPath(atributes.Path.path());
    QString newPhotoPath(Path.path());
    newPhotoPath.append("/");
    newPhotoPath.append(QString::number(atributes.ID));
    newPhotoPath.append(".");
    newPhotoPath.append(QFileInfo(oldPhotoPath).suffix());


    if(!QFile::copy(oldPhotoPath,newPhotoPath)){
        qDebug() << "Pagina::createPhoto->ERRO copying file:" << oldPhotoPath << "to" << newPhotoPath;
        return nullptr;
    }

    atributes.Path.setPath(newPhotoPath);

    Foto* newFoto=new Foto(atributes);

    if(!oGestor->addPhoto(&atributes)){
        delete newFoto;
        return nullptr;
    }
    else{
        qDebug() << "Pagina::createPhoto->Photo Saved";
        Photos->append(newFoto);
        return newFoto;
    }
}

//----------------PRIVATE----------------------------//
bool Pagina::createFolder(){
    if(!Path.exists()){
        qDebug() << "Pagina::createFolder()->ERROR Path to folder doesn't exist!!";
    }
    QString folderName(createFolderName());
    QString newFolderName;
    newFolderName = folderName;
    qDebug() << "Pagina::createFolder()->Creating Folder";
    for(int i=1;!Path.mkdir(newFolderName);i++){
        newFolderName.clear();
        newFolderName = folderName;
        newFolderName.append("(");
        newFolderName.append(QString::number(i));
        newFolderName.append(")");
        qDebug() << "Pagina::createFolder()->ERROR Creating Folder:" << newFolderName;
        if(i==20){
            qDebug() << "Pagina::createFolder()->ERROR Creating Folder: IM OUT!!";
            return false;
        }
    }

    Path.cd(newFolderName);
    return true;
}
