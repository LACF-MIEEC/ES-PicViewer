#include "addpagedialog.h"
#include "ui_addpagedialog.h"

#include "CustomClasses/pagina.h"

AddPageDialog::AddPageDialog(pageType_t tipo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPageDialog)
{
    ui->setupUi(this);
    switch(tipo){
    case viagem:
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();
        break;

    case festa:
        this->findChild<QLabel*>("label_Date")->setText("Data:");

        this->findChild<QLabel*>("label_DateEnd")->hide();
        this->findChild<QDateEdit*>("DateEnd")->setEnabled(false);
        this->findChild<QDateEdit*>("DateEnd")->hide();
        break;

    case coisaPessoa:
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();

        this->findChild<QLabel*>("label_Date")->setText("Sem Detalhes Adicionais.");

        this->findChild<QDateEdit*>("Date")->setEnabled(false);
        this->findChild<QDateEdit*>("Date")->hide();

        this->findChild<QLabel*>("label_DateEnd")->hide();
        this->findChild<QDateEdit*>("DateEnd")->setEnabled(false);
        this->findChild<QDateEdit*>("DateEnd")->hide();
        break;

    case outro:
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();
        break;
    }//end Switch
}

AddPageDialog::~AddPageDialog()
{
    delete ui;
}

void AddPageDialog::on_buttonBox_accepted()
{
    QString Desc = this->findChild<QPlainTextEdit*>("Description")->toPlainText();
    if(Desc.isEmpty()){
        //Tem de  haver descrição
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Parametros insuficientes", "Tem de fornecer uma descrição para a página",
                                             QMessageBox::Ok,this);

        error->exec();
        error->deleteLater();
        return;
    }
    //Falta confirmar restantes parametros

    emit pageAccepted(this);
    this->hide();
}

void AddPageDialog::on_buttonBox_rejected()
{
    this->close();
    this->deleteLater();
}
