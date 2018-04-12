#include "pagina.h"

Pagina::Pagina(PageParam atributes)
{
    ID          =   atributes.ID;
    Description =   atributes.Description;
    Path        =   atributes.Path;
    Parent      =   atributes.Parent;
    oGestor     =   atributes.Gestor;

    if(RunMode.testFlag(Setup::Boot)){
        Photos = new QVector<Foto*>();
        QVector<PhotoParam*> *PhotoAtributes = oGestor->getPhotos(&atributes);
        for(int i=0;i<PhotoAtributes->size();i++){
            PhotoAtributes->at(i)->Parent=this;
            Photos->append(new Foto(*PhotoAtributes->at(i)));
        }
        delete PhotoAtributes;
    }
}
void Pagina::deleteSelf(){
    for(int i=0;Photos->size();i++){
        Photos->at(i)->deleteSelf();
    }
    delete Photos;
    delete this;
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

int Pagina::createFolder(QString folderName){
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

