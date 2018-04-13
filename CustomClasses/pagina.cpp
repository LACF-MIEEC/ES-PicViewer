#include "pagina.h"

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
    for(int i=0;Photos->size();i++){
        delete Photos->at(i);
    }
    delete Photos;
}

bool Pagina::loadPhotos(GestorBD* gestor){
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
        PhotoAtributes->at(i)->Parent=this;
        Photos->append(new Foto(*PhotoAtributes->at(i)));
    }
    delete PhotoAtributes;

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

QVector<Foto*>* Pagina::getPhotos(){
    return Photos;
}

Album* Pagina::parent(){
    return Parent;
}

//-------------------Create--------------------------//

Foto* Pagina::createPhoto(PhotoParam atributes){





    Foto* newFoto=new Foto(atributes);
    if(!oGestor->addPhoto(&atributes)){
        qDebug() << "Unable to Save Photo";
        delete newFoto;
        return nullptr;
    }
    else{
        qDebug() << "Photo Saved";
        Photos->append(newFoto);
        return newFoto;
    }
}

//----------------PRIVATE----------------------------//
bool Pagina::createFolder(){
    QString folderName(createFolderName());
    QString newFolderName;
    newFolderName = folderName;
    qDebug() << "Pagina::createFolder()->Creating Folder";
    for(int i=1;!Path.mkdir(newFolderName);i++){
        newFolderName.clear();
        newFolderName = folderName;
        newFolderName.append("(");
        newFolderName.append(i);
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
