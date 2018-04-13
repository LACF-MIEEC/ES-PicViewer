#ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "pagina.h"

class Album
{
public:

    Album(AlbumParam atributes);
    ~Album();

    bool loadPages(GestorBD *gestor=0);

    bool createFolder();
    //----------------Get Atributes----------------//

    int getID();
    QString getName();
    QString getDescription();
    QDir getPath();
    pageType_t getPageType();

    QVector<Pagina *> *getPages();

    ListaAlbuns* parent();

    //-------------------Create--------------------//

    Pagina* createPage(PageParam atributes);

    Foto* createPhoto(PhotoParam atributes, Pagina* destination);


    /* MODIFICATIONS NOT YET IMPLEMENTED
    int setName(QString newName);
    void setDescription(QString newDesc);
    */

    /* DELETE AND MOVE NOT YET IMPLEMENTED
    int acceptPage(Pagina* page);
    int removePage(Pagina* page);
    int deletePage(Pagina* page);
    */

    //int acceptPhoto(Pagina* page, Foto* photo); //Mais vale ir logo à página se já tenho o ponteiro

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate date);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


private:

    QString createFolderName();

    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;

    ListaAlbuns* Parent;
    GestorBD* oGestor;
    QVector<Pagina*> *Pages;

};

#endif // ALBUM_H
