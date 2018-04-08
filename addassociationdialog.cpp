#include "addassociationdialog.h"
#include "ui_addassociationdialog.h"

AddAssociationDialog::AddAssociationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAssociationDialog)
{
    ui->setupUi(this);
}

AddAssociationDialog::~AddAssociationDialog()
{
    delete ui;
}
