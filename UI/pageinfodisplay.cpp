#include "pageinfodisplay.h"
#include "ui_pageinfodisplay.h"

PageInfoDisplay::PageInfoDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageInfoDisplay)
{
    ui->setupUi(this);
}

PageInfoDisplay::~PageInfoDisplay()
{
    delete ui;
}
