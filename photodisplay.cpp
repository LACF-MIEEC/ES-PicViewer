#include "photodisplay.h"
#include "ui_photodisplay.h"

PhotoDisplay::PhotoDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoDisplay)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);
}

PhotoDisplay::~PhotoDisplay()
{
    delete ui;
}
