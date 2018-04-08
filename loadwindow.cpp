#include "loadwindow.h"
#include "ui_loadwindow.h"

LoadWindow::LoadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);
}

LoadWindow::~LoadWindow()
{
    delete ui;
}
