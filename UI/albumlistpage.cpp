#include "albumlistpage.h"
#include "ui_albumlistpage.h"

AlbumListPage::AlbumListPage(QWidget *parent, QString Text) :
    QWidget(parent),
    ui(new Ui::AlbumListPage)
{
    ui->setupUi(this);
    ui->Text->setText(Text);
}

AlbumListPage::~AlbumListPage()
{
    delete ui;
}
