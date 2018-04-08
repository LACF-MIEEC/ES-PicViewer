#include "managepeople.h"
#include "ui_managepeople.h"

ManagePeople::ManagePeople(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagePeople)
{
    ui->setupUi(this);
}

ManagePeople::~ManagePeople()
{
    delete ui;
}

void ManagePeople::on_Voltar_clicked()
{
    this->hide();
}
void ManagePeople::addItemPeopleList(QString ItemName){

    this->findChild<QListWidget*>("PeopleList")->addItem(new QListWidgetItem(QIcon(":/Icons/bin/Icons/People.png"),ItemName));
}
