#include "albumlistitem.h"
#include "ui_albumlistitem.h"

#include "CustomClasses/album.h"

AlbumListItem::AlbumListItem(Album* album,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListItem)
{
    ui->setupUi(this);
    ui->Text->setText(album->getName());

    thisAlbum=album;

}

AlbumListItem::~AlbumListItem()
{
    delete ui;
}
Album* AlbumListItem::getAlbum(){
    return thisAlbum;
}


