#include "foto.h"

Foto::Foto(PhotoParam atributes)
{
    ID      = atributes.ID;
    Path    = atributes.Path;
    Parent  = atributes.Parent;
    oGestor = atributes.Gestor;

    if(RunMode.testFlag(Setup::Boot)){
        /*QVector<PhotoParam*> PhotoAtributes = oGestor->getPhotos(this);
        for(int i=0;PhotoAtributes.size();i++){
            Photos.append(new Foto(PhotoAtributes.at(i)));
        }*/
        RunMode = Setup::RunTime;
    }
    if(RunMode.testFlag(Setup::RunTime)){
        if(!oGestor->addPhoto(this))
            qDebug << "Unable to Save Page";
    }

}

void Foto::deleteSelf(){

    delete this;
}


int Foto::getID(){
    return ID;
}

QDir Foto::getPath(){
    return Path;
}

QVector<Pessoa*> Foto::getPeople(){
    return People;
}

Pagina* Foto::parent(){
    return Parent;
}

