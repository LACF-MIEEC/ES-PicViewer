#include "addpersondialog.h"
#include "ui_addpersondialog.h"

AddPersonDialog::AddPersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::on_buttonBox_rejected()
{
    this->close();
    this->deleteLater();
}

void AddPersonDialog::on_buttonBox_accepted()
{
    //Nome
    QString Name = this->findChild<QLineEdit*>("Name")->text();
    if(Name.isEmpty()){
       //Tem de  haver nome
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Parametros insuficientes", "Tem de fornecer um nome!",
                                             QMessageBox::Ok,this);

        error->exec();
        error->deleteLater();
       return;
    }
    //Nascimento
    //EM FALTA
    QDate Birth = this->findChild<QDateEdit*>("Birth")->date();
    if(!Birth.isValid()){
        //Tem de estar selecionado um genero
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Parametros inválidos", "Forneça um data válida",
                                                 QMessageBox::Ok,this);

        error->exec();
        error->deleteLater();
        return;
    }
    //Genero
    QString Gender= this->findChild<QComboBox*>("Gender")->currentText();
    if(Gender.isEmpty()){
        //Tem de estar selecionado um genero
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Parametros insuficientes", "Tem de selecionar um género",
                                             QMessageBox::Ok,this);

        error->exec();
        error->deleteLater();
        return;
    }
    //Relação
    QString Bond = this->findChild<QLineEdit*>("Bond")->text();
    if(Bond.isEmpty()){
       //Tem de  haver relação
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Parametros insuficientes", "Tem de fornecer a relação!",
                                             QMessageBox::Ok,this);

        error->exec();
        error->deleteLater();
       return;
    }

    emit personAccepted(this);
    this->hide();

}
