#include "albumlistitem.h"
#include "ui_albumlistitem.h"

AlbumListItem::AlbumListItem(QWidget *parent, QString Text) :
    QWidget(parent),
    ui(new Ui::AlbumListItem)
{
    ui->setupUi(this);
    ui->Text->setText(Text);
}

AlbumListItem::~AlbumListItem()
{
    delete ui;
}
Album* AlbumListItem::getAlbum(){
    return thisAlbum;
}


