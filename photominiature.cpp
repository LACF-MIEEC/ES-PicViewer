#include "photominiature.h"
#include "ui_photominiature.h"

PhotoMiniature::PhotoMiniature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoMiniature)
{
    ui->setupUi(this);

}

PhotoMiniature::~PhotoMiniature()
{
    delete ui;
}
