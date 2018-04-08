#include "addalbumdialog.h"
#include "ui_addalbumdialog.h"

AddAlbumDialog::AddAlbumDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAlbumDialog)
{
    ui->setupUi(this);
}

AddAlbumDialog::~AddAlbumDialog()
{
    delete ui;
}

void AddAlbumDialog::on_BrowseButton_clicked()
{
    //Alterar Direcótorio base para uma predifinição
    QString dir = QFileDialog::getExistingDirectory(this, "Abrir Pasta",
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    );

    if(!dir.isNull()){
        this->findChild<QLineEdit*>("Directory")->clear();
        this->findChild<QLineEdit*>("Directory")->insert(dir);
    }
}

void AddAlbumDialog::on_Result_accepted()
{
    //************************************************************************
    //Fazer Validação dos atributos (Ver se existem e criar os nome das pastas)

    //Nome do Album
    QString Name = this->findChild<QLineEdit*>("Name")->text();
    if(Name.isEmpty()){
       //Tem de  haver nome
        QMessageBox *error = new QMessageBox(QMessageBox::Information,"Parametros insuficientes", "Tem de fornecer um nome para o album",
                                             QMessageBox::Ok,this);

        error->exec();
       return;
    }

    //Descrição do Album
    QString Desc = this->findChild<QPlainTextEdit*>("Description")->toPlainText();

    if(Desc.isEmpty()){
       //Tem de  haver descrição
        QMessageBox *error = new QMessageBox(QMessageBox::Information,"Parametros insuficientes", "Tem de fornecer uma descrição para o album",
                                             QMessageBox::Ok,this);

        error->exec();
        return;
    }

    //Tipo de Página
    QString Type= this->findChild<QComboBox*>("Type")->currentText(); //Podiamos usar um ID em vez de Texto??
    if(Type.isEmpty()){
        //Tem de estar selecionado um tipo
        QMessageBox *error = new QMessageBox(QMessageBox::Information,"Parametros insuficientes", "Tem de selecionar um tipo de pagina para o album",
                                             QMessageBox::Ok,this);

        error->exec();
        return;
    }

    //Localização do Album
    QString Dir = this->findChild<QLineEdit*>("Directory")->text();
    if(Dir.isEmpty()){
       //Tem de  haver directorio
       QMessageBox *error = new QMessageBox(QMessageBox::Information,"Parametros insuficientes", "Tem de fornecer uma localização para o album",
                                            QMessageBox::Ok,this);

       error->exec();
       return;
    }
    //Verificar se localização é valida(existe);
    QDir Path(Dir);
    if (!Path.exists()){
        QMessageBox *error = new QMessageBox(QMessageBox::Warning,"Localização Inválida", "Localização Inexistente",
                                             QMessageBox::Ok,this);

        error->exec();
        return;
    }
    this->hide();
}

void AddAlbumDialog::on_Result_rejected()
{
    this->hide();
}
