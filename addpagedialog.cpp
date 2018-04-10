#include "addpagedialog.h"
#include "ui_addpagedialog.h"

AddPageDialog::AddPageDialog(QString Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPageDialog)
{
    ui->setupUi(this);

    if(Type.compare("Viagem")== 0){
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();

    }else if(Type.compare("Festa")==0){
        this->findChild<QLabel*>("label_Date")->setText("Data:");

        this->findChild<QLabel*>("label_DateEnd")->hide();
        this->findChild<QDateEdit*>("DateEnd")->setEnabled(false);
        this->findChild<QDateEdit*>("DateEnd")->hide();


    }else if(Type.compare("Coisa ou Pessoa")==0){
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();

        this->findChild<QLabel*>("label_Date")->setText("Sem Detalhes Adicionais.");

        this->findChild<QDateEdit*>("Date")->setEnabled(false);
        this->findChild<QDateEdit*>("Date")->hide();

        this->findChild<QLabel*>("label_DateEnd")->hide();
        this->findChild<QDateEdit*>("DateEnd")->setEnabled(false);
        this->findChild<QDateEdit*>("DateEnd")->hide();

    }else if(Type.compare("Outro")==0){
        this->findChild<QLabel*>("label_Type")->hide();
        this->findChild<QLineEdit*>("Type")->setEnabled(false);
        this->findChild<QLineEdit*>("Type")->hide();
    }

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
