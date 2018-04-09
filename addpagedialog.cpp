#include "addpagedialog.h"
#include "ui_addpagedialog.h"

AddPageDialog::AddPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPageDialog)
{
    ui->setupUi(this);
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
        return;
    }
    else{
        emit pageAccepted(this);
        this->hide();
    }
}

void AddPageDialog::on_buttonBox_rejected()
{
    this->close();
}
