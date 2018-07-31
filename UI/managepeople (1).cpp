#include "managepeople.h"
#include "ui_managepeople.h"

#include "CustomClasses/gestorbd.h"
#include "CustomClasses/foto.h"
#include "CustomClasses/pagina.h"
#include "CustomClasses/album.h"
#include "CustomClasses/listaalbuns.h"
#include "CustomClasses/listapessoas.h"
#include "CustomClasses/pessoa.h"

ManagePeople::ManagePeople(GestorBD *gestor,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagePeople)
{
    ui->setupUi(this);

    aListaPessoas= new ListaPessoas(gestor);

    oGestor=gestor;

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

    PersonParam atributes;

    atributes.Name = Dialog->findChild<QLineEdit*>("Name")->text();
    atributes.Birth = Dialog->findChild<QDateEdit*>("Birth")->date();

    if(QString::compare(Dialog->findChild<QComboBox*>("Gender")->currentText(),"Masculino")){
        atributes.Gender=masculino;
    }
    else if(QString::compare(Dialog->findChild<QComboBox*>("Gender")->currentText(),"Feminino")){
        atributes.Gender=feminino;
    }

    atributes.Bond  = Dialog->findChild<QLineEdit*>("Bond")->text();

    atributes.Parent=aListaPessoas;
    atributes.Gestor=oGestor;

    Pessoa* newPerson = aListaPessoas->createPerson(atributes);

    QMessageBox *msg;
    if(newPerson==nullptr){
        msg = new QMessageBox(QMessageBox::Warning,"Erro", "Falha ao criar Pessoa!",
                                             QMessageBox::Ok,this);
        msg->exec();
        msg->deleteLater();
        Dialog->close();
        Dialog->deleteLater();
        return;
    }
    addItemPeopleList(newPerson);

    Dialog->close();
    Dialog->deleteLater();
    //Apresenta Mensagem de confirmação
    msg = new QMessageBox(QMessageBox::Information,"Pessoa Criada", "A Pessoa foi criada com sucesso!",
                                         QMessageBox::Ok,this);

    msg->exec();
    msg->deleteLater();
}

void ManagePeople::on_PeopleList_itemClicked(QListWidgetItem *item)
{
    Pessoa* SelectedPerson = aListaPessoas->getPeople()->at(ui->PeopleList->currentRow());

    ui->Name->setText(SelectedPerson->getName());
    ui->Birth->setText(SelectedPerson->getBirth().toString(Qt::ISODate));
    ui->Bond->setText(SelectedPerson->getBond());

    switch (SelectedPerson->getGender()){
    case masculino:
        ui->Gender->setText("Masculino");
        break;
    case feminino:
        ui->Gender->setText("Feminino");
        break;
    }
}
