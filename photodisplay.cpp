#include "photodisplay.h"
#include "ui_photodisplay.h"

PhotoDisplay::PhotoDisplay(const QImage &newImage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoDisplay)
{
    ui->setupUi(this);

    Image=newImage;

   // this->showFullScreen();
    this->resize(parent->size());
    this->findChild<QLabel*>("Photo")->setPixmap(QPixmap::fromImage(Image));
    this->findChild<QLabel*>("Photo")->adjustSize();

}

PhotoDisplay::~PhotoDisplay()
{
    delete ui;
}

void PhotoDisplay::on_Return_clicked()
{
    this->close();
    this->deleteLater();
}
