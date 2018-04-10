#include "albuminfodisplay.h"
#include "ui_albuminfodisplay.h"

AlbumInfoDisplay::AlbumInfoDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumInfoDisplay)
{
    ui->setupUi(this);
}

AlbumInfoDisplay::~AlbumInfoDisplay()
{
    delete ui;
}
