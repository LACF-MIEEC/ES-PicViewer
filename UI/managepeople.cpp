#include "managepeople.h"
#include "ui_managepeople.h"

ManagePeople::ManagePeople(GestorBD *gestor,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagePeople)
{
    ui->setupUi(this);

    aListaPessoas= new ListaPessoas(gestor);

    aListaPessoas->loadPeople();

    //------------------------------------
    //Carregar Pessoas

    for(int i=0;i<aListaPessoas->getPeople()->size();i++){
        addItemPeopleList(aListaPessoas->getPeople()->at(i));
    }
}

ManagePeople::~ManagePeople()
{
    delete aListaPessoas;
    delete ui;
}

void ManagePeople::on_Voltar_clicked()
{
    this->hide();
}
void ManagePeople::addItemPeopleList(Pessoa* newItem){

    this->findChild<QListWidget*>("PeopleList")->addItem(new QListWidgetItem(QIcon(":/Icons/bin/Icons/People.png"),newItem->getName()));
}

void ManagePeople::on_DelPerson_clicked()
{
    QMessageBox *msg = new QMessageBox(QMessageBox::Question,"Eliminar Pessoa", "Tem a certeza?",
                                          QMessageBox::Ok | QMessageBox::Cancel,this);

    int Role = msg->exec();

    msg->deleteLater();

    if(Role)//Cancel
        return;
    else{

        //Delete Person
    }

}

void ManagePeople::on_AddPerson_clicked()
{
    AddPersonDialog *Dialog = new AddPersonDialog();

    connect(Dialog,SIGNAL(personAccepted(AddPersonDialog*)), this, SLOT(addPerson(AddPersonDialog*)));
    Dialog->show();
}

void ManagePeople::addPerson(AddPersonDialog *Dialog){

    //Criar o ALbum e Actualizar a interface

    QString Name = Dialog->findChild<QLineEdit*>("Name")->text();
    QDate Birth = Dialog->findChild<QDateEdit*>("Birth")->date();
    QString Gender = Dialog->findChild<QComboBox*>("Gender")->currentText();
    QString Bond  = Dialog->findChild<QLineEdit*>("Bond")->text();

    //ListaPesoas::createPerson();
    //addItemPeopleList();


    Dialog->close();
    Dialog->deleteLater();
    //Apresenta Mensagem de confirmação
    QMessageBox *msg = new QMessageBox(QMessageBox::Information,"Pessoa Criada", "A Pessoa foi criada com sucesso!",
                                         QMessageBox::Ok,this);

    msg->exec();
    msg->deleteLater();
}
