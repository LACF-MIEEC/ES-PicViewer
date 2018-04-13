#include "photominiature.h"
#include "ui_photominiature.h"

PhotoMiniature::PhotoMiniature(Foto* photo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoMiniature)
{
    ui->setupUi(this);
    thisPhoto=photo;
}

PhotoMiniature::~PhotoMiniature()
{
    delete ui;
}

Foto* PhotoMiniature::getPhoto(){
    return thisPhoto;
}

