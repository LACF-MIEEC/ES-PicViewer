#include "photominiature.h"
#include "ui_photominiature.h"

PhotoMiniature::PhotoMiniature(int *FotoInt, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoMiniature)
{
    ui->setupUi(this);
    Foto=123999;
}

PhotoMiniature::~PhotoMiniature()
{
    delete ui;
}
