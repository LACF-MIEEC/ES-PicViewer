#include "albumlistpage.h"
#include "ui_albumlistpage.h"


AlbumListPage::AlbumListPage(QString text,Pagina* page, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListPage)
{
    ui->setupUi(this);
    ui->Text->setText(text);

    thisPage=page;
}

AlbumListPage::~AlbumListPage()
{
    delete ui;
}

Pagina* AlbumListPage::getPage(){
    return thisPage;
}
