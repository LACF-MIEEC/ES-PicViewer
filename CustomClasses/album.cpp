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

    Pages=new QVector<Pagina*>();

}

Album::~Album(){
    for(int i=0;Pages->size();i++){
        delete Pages->at(i);
    }
    delete Pages;
}

bool Album::loadPages(GestorBD *gestor){

    if(gestor==0)
        gestor=oGestor;
    if(gestor==0){
        qDebug() << "Album.load():ERROR GestorBD not set.";
        return false;
    }

    AlbumParam atributes;
    atributes.ID=ID;
    QVector<PageParam*> *PageAtributes = gestor->getPages(&atributes);
    if(!PageAtributes){
        qDebug() << "Album.load(): ERROR GestorBD->Fail to load.";
        delete PageAtributes;
        return false;
    }

    Pages->clear();
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

    return true;
}

//----------------Get Atributes----------------//


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

    if(!newPage->createFolder()){
        delete newPage;
        return nullptr;
    }
    else if(!oGestor->addPage(&atributes)){
        delete newPage;
        if(Path.rmdir(newPage->getPath().dirName())){
            //BIG PROBLEM
            qDebug() << "Album::createFolder()->ERROR Removing Folder:" << newPage->getPath().dirName();
            return nullptr;
        }
        return nullptr;
    }

    Pages->append(newPage);
    return newPage;
}

Foto* Album::createPhoto(PhotoParam atributes, Pagina* destination){
    return destination->createPhoto(atributes);
}

bool Album::createFolder(){
    QString folderName = createFolderName();
    QString newFolderName;
    newFolderName = folderName;
    qDebug() << "Album::createFolder()->Creating Folder";
    for(int i=1;!Path.mkdir(newFolderName);i++){
        newFolderName.clear();
        newFolderName = folderName;
        newFolderName.append("(");
        newFolderName.append(i);
        newFolderName.append(")");
        qDebug() << "Album::createFolder()->ERROR Creating Folder:" << newFolderName;
        if(i==20){
            qDebug() << "Album::createFolder()->ERROR Creating Folder: IM OUT!!";
            return false;
        }
    }

    Path.cd(newFolderName);
    return true;
}

QString Album::createFolderName(){
    QString FolderName;
    //Tirar espaços e caracteres especiais;

  //QString NormalizedName(Name.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))).replace(" ", "_").normalized(QString::NormalizationForm_D));
    QString NormalizedName(Name.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\[\]\\\]"))).replace(" ", "_").normalized(QString::NormalizationForm_D));
    for (int i=0;i<NormalizedName.length(); i++)
    {
        // strip diacritic marks
        if (NormalizedName.at(i).category()!=QChar::Mark_NonSpacing &&
                NormalizedName.at(i).category()!=QChar::Mark_SpacingCombining &&
                NormalizedName.at(i).category()!=QChar::Mark_Enclosing)
        {
            FolderName.append(NormalizedName.at(i));
        }
    }

    FolderName.append("_");
    FolderName.append(QString::number(ID));
    return FolderName;
}
