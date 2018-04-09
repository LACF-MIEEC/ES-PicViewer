#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wPeople = new ManagePeople();

    ui->setupUi(this);

    //=================================
    //Construir Janela
    //Esta Rotina talvez seja melhor ser feita por parte da classe Gestora
    //------------------------------------
    //Caregar Albuns e Páginas
    QStringList Pages;

    Pages << "Pagina 1" << "Mais Uma" << "É a ultima";

    this->addItemAlbumTree("Album Velho", Pages);
    this->addItemAlbumTree("Album Novo", Pages);
    //------------------------------------
    //Carregar Fotos


    //------------------------------------
    //Carregar Pessoas
    wPeople->addItemPeopleList("Gilberto");
    wPeople->addItemPeopleList("Palmira");
    wPeople->addItemPeopleList("Arminda");
    wPeople->addItemPeopleList("Cesário");
    wPeople->addItemPeopleList("Alcides");
    wPeople->addItemPeopleList("Josefina");
    wPeople->addItemPeopleList("Serafim");
    wPeople->addItemPeopleList("Eulália");

    this->addItemPeopleList("Alcides");
    this->addItemPeopleList("Josefina");
    this->addItemPeopleList("Serafim");
    this->addItemPeopleList("Eulália");



    this->setWindowState(Qt::WindowMaximized);

    ui->PhotoDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PhotoDisplay->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PhotoDisplay->setColumnCount(4);
    //ui->PhotoDisplay->setIconSize(QSize(ui->PhotoDisplay->horizontalHeader()->sectionSize(0),ui->PhotoDisplay->horizontalHeader()->sectionSize(0)));


    ui->Title->setText("PicViewer - Bem Vindo!!");

    AlbumInfoDisplay *widget1= new AlbumInfoDisplay();
    AlbumInfoDisplay *widget2= new AlbumInfoDisplay();

    widget1->resize(ui->Info->sizeHint());
    widget2->resize(ui->Info->sizeHint());

    ui->Info->removeItem(0);
    ui->Info->removeItem(0);
    ui->Info->addItem(widget1,"Informações do Álbum");
    ui->Info->addItem(widget2,"Informações da Página");


    ui->AlbumList->collapseAll();

}

MainWindow::~MainWindow()
{
    /*
        Serão executadas as rotinas de fecho aqui.
        Talvez Chamar uma funçao de fecho,
            para engobar outras opções de fecho p.e. botão [X].
    */

    delete ui;
}

void MainWindow::addItemAlbumTree(QString ItemName, QStringList PageName)
{
    QTreeWidgetItem *TreeItem = new QTreeWidgetItem(ui->AlbumList);

    AlbumListItem *ItemWidget = new AlbumListItem(NULL,ItemName);

    //Adicionar Crianças
    QTreeWidgetItem *ChildItem;
    AlbumListPage *ChildWidget;

    for(int i=0; i < PageName.size() ;i++){
        ChildItem= new QTreeWidgetItem(TreeItem);
        ChildWidget= new AlbumListPage(NULL,QString(PageName.at(i)));

        ui->AlbumList->setItemWidget(ChildItem,0,ChildWidget);
        ChildItem->setSizeHint(0,ChildWidget->sizeHint());
    }
    TreeItem->setSizeHint(0,ItemWidget->sizeHint());
    ui->AlbumList->setItemWidget(TreeItem,0,ItemWidget);

}

void MainWindow::addItemPeopleList(QString ItemName){

    ui->PeopleList->addItem(new QListWidgetItem(QIcon(":/Icons/bin/Icons/People.png"),ItemName));

}

void MainWindow::on_AlbumList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString AlbumName, PageName="";

    if(!current->parent()){ //Se current Album

        current->setExpanded(true);
        //Alterar restantes sitios da frame onde o album ou as suas caracteristicas são definidas
        AlbumName = ui->AlbumList->itemWidget(current,0)->findChild<QLabel*>("Text")->text();


        ui->Title->setText(QString(AlbumName));
        //-------------
        //Retirar Fotos do display
        ui->PhotoDisplay->setRowCount(0);


        if(previous){
            if(!previous->parent()){ //Se Anterior for Album
                previous->setExpanded(false);
            }
            else{ //Se Anterior for página
                if(previous->parent()!=current)
                    previous->parent()->setExpanded(false);
            }
        }
    }
    else{ //Se current Página
        //Alterar restantes sitios da frame onde o album/pagina ou as suas caracteristicas são definidas
        AlbumName = ui->AlbumList->itemWidget(current->parent(),0)->findChild<QLabel*>("Text")->text();
        PageName=  ui->AlbumList->itemWidget(current,0)->findChild<QLabel*>("Text")->text();

        ui->Title->setText(QString(AlbumName + " : " + PageName));
        //-------------
        //Colocar Fotos no Display



        //Aceder a objecto página
        //obter path das fotos

        QStringList PhotoPath;

        PhotoPath << ":/Photos/bin/Images/Login_Background.png" << ":/Photos/bin/Images/logo.png";


        //obter pessoas das fotos
        //???????????

        ui->PhotoDisplay->setRowCount(PhotoPath.size()/ui->PhotoDisplay->columnCount()+1);
        int row=0; int column=0;


        QTableWidgetItem *Item;
        PhotoMiniature *Miniature;

        for(int i=0;i<PhotoPath.size();i++){

            QImageReader reader(PhotoPath.at(i));
            reader.setAutoTransform(true);
            const QImage newImage = reader.read();
            if (newImage.isNull()) {
                QMessageBox::information(this, QApplication::applicationDisplayName(),
                                             tr("Cannot load %1: %2")
                                             .arg(QDir::toNativeSeparators(PhotoPath.at(i)), reader.errorString()));
                return;
            }

            Miniature = new PhotoMiniature();

            Miniature->findChild<QLabel*>("Photo")->setPixmap(QPixmap::fromImage(newImage).scaled(
                                                                  QSize(ui->PhotoDisplay->horizontalHeader()->sectionSize(0),ui->PhotoDisplay->horizontalHeader()->sectionSize(0))
                                                              ,Qt::KeepAspectRatio));
            Miniature->findChild<QLabel*>("Photo")->adjustSize();

            Item = new QTableWidgetItem();//QIcon(QPixmap(PhotoPath.at(i)).scaled(ui->PhotoDisplay->iconSize(),Qt::KeepAspectRatio)),QString(""));


            Item->setSizeHint(QSize(ui->PhotoDisplay->horizontalHeader()->sectionSize(0),ui->PhotoDisplay->horizontalHeader()->sectionSize(0)));

            ui->PhotoDisplay->setItem(row,column,Item);

            ui->PhotoDisplay->setCellWidget(row,column,Miniature);

            column++;
            if(column==ui->PhotoDisplay->columnCount()){
                column=0;
                row++;
            }
        }

    }

}

void MainWindow::on_Exit_triggered()
{
    /*
        Serão executadas as rotinas de fecho aqui.
        Talvez Chamar uma funçao de fecho,
            para engobar outras opções de fecho p.e. botão [X].
    */
    QCoreApplication::quit();
}

void MainWindow::on_ManagePeople_clicked()
{
    wPeople->show();
}

void MainWindow::on_AddAssociation_clicked()
{
    AddAssociationDialog *ChoosePerson = new AddAssociationDialog(this);

    for(int i=0; i < wPeople->findChild<QListWidget*>("PeopleList")->count(); i++){

        ChoosePerson->findChild<QListWidget*>("PeopleList")->addItem(wPeople->findChild<QListWidget*>("PeopleList")->item(i)->clone());
    }

    ChoosePerson->exec();

    connect(ChoosePerson->findChild<QDialogButtonBox*>("OK"), SIGNAL(accepted()),ChoosePerson, SLOT(accept()));

    if(ChoosePerson->result()==1){
        QString Pessoa = ChoosePerson->findChild<QListWidget*>("PeopleList")->currentItem()->text();
        QList<QListWidgetItem*> Matches = ui->PeopleList->findItems(Pessoa,Qt::MatchFixedString | Qt::MatchCaseSensitive);

        if(Matches.isEmpty()){
            addItemPeopleList(Pessoa);
        }

        else{
            QMessageBox *AlreadyAssociated =new QMessageBox(this);

            AlreadyAssociated->setText("Esta pessoa já está associada à foto selecionada.");
            AlreadyAssociated->setWindowTitle("Aviso!!");
            AlreadyAssociated->addButton("OK",QMessageBox::AcceptRole);

            AlreadyAssociated->exec();
        }
    }

}

void MainWindow::on_RemoveAssociation_clicked()
{
    QListWidgetItem *toDelete = ui->PeopleList->takeItem(ui->PeopleList->currentRow());
    if(toDelete){
        toDelete->~QListWidgetItem();
    }
}

void MainWindow::on_AddAlbum_clicked()
{
    AddAlbumDialog *Dialog = new AddAlbumDialog();

    connect(Dialog,SIGNAL(albumAccepted(AddAlbumDialog*)), this, SLOT(addAlbum(AddAlbumDialog*)));
    Dialog->show();
}

void MainWindow::addAlbum(AddAlbumDialog *Dialog){

        //Criar o ALbum e Actualizar a interface

        QString Name = Dialog->findChild<QLineEdit*>("Name")->text();
        QString Desc = Dialog->findChild<QPlainTextEdit*>("Description")->toPlainText();
        QString Type = Dialog->findChild<QComboBox*>("Type")->currentText();
        QString Dir  = Dialog->findChild<QLineEdit*>("Directory")->text();

        //ListaAlbuns::createAlbum();
        //addItemAlbumTree

        //Apresenta Mensagem de confirmação
        QMessageBox *msg = new QMessageBox(QMessageBox::Information,"Album Criado", "O Álbum foi criado com sucesso!",
                                             QMessageBox::Ok,this);

        msg->exec();
        Dialog->close();
        Dialog->deleteLater();
}

void MainWindow::on_AddPage_clicked()
{

    QString AlbumName;

    //Altera caixa de Dialogo para os detalhes corresponderem ao tipo de Página

    if(!ui->AlbumList->currentItem()->parent()){ //Se estiver o Album Seleccionado
        AlbumName = ui->AlbumList->itemWidget(ui->AlbumList->currentItem(),0)->findChild<QLabel*>("Text")->text();
    }
    else{ //Caso seja um página procurar o album pertencente
        AlbumName = ui->AlbumList->itemWidget(ui->AlbumList->currentItem()->parent(),0)->findChild<QLabel*>("Text")->text();
    }

    //MISSING**************************
    //Get ALbum Type

    // AlbumList Search Album ?? By ID or By Name?

    QString Type; //Talvez seja melhor definir um ID [1,4] para definir os tipos

    Type.operator=("Coisa ou Pessoa"); //só para teste (remover depois)
    //*********************************
    AddPageDialog *Dialog = new AddPageDialog(Type);

    connect(Dialog,SIGNAL(pageAccepted(AddPageDialog*)), this, SLOT(addPage(AddPageDialog*)));
    Dialog->show();
}

void MainWindow::addPage(AddPageDialog *Dialog){

       //Criar a Página e Actualizar a interface
       QString Desc = Dialog->findChild<QPlainTextEdit*>("Description")->toPlainText();

       //Alguns destes podem não se aplicar,  dependendo do tipo de página
       QDate Date = Dialog->findChild<QDateEdit*>("Date")->date();
       QDate EndDate = Dialog->findChild<QDateEdit*>("DateEnd")->date();
       QString PartyType = Dialog->findChild<QLineEdit*>("Type")->text();


       //ListaAlbuns::createPage();
       //addItemAlbumTree

       //Apresenta Mensagem de confirmação
       QMessageBox *msg = new QMessageBox(QMessageBox::Information,"Página Criada", "A Página foi criada com sucesso!",
                                             QMessageBox::Ok,this);

       msg->exec();
       Dialog->close();
       Dialog->deleteLater();
}

void MainWindow::on_AddPhoto_clicked()
{
    if(!ui->AlbumList->currentItem()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Warning,"Aviso", "Selecione um album e uma página para adicionar a foto!",
                                              QMessageBox::Ok,this);
        msg->exec();
        return;
    }
    else if(!ui->AlbumList->currentItem()->parent()){ //Se estiver o Album Seleccionado
        QMessageBox *msg = new QMessageBox(QMessageBox::Warning,"Página Inválida", "Selecione uma página para adicionar a foto!",
                                              QMessageBox::Ok,this);
        msg->exec();
        return;
    }
    else{ //Caso seja um página procurar o album pertencente
        QString AlbumName = ui->AlbumList->itemWidget(ui->AlbumList->currentItem()->parent(),0)->findChild<QLabel*>("Text")->text();
        QString PageName  = ui->AlbumList->itemWidget(ui->AlbumList->currentItem(),0)->findChild<QLabel*>("Text")->text();

    }
    QStringList photosDir = QFileDialog::getOpenFileNames(this, "Selecione uma ou mais Fotos",
                                                    QDir::homePath(),
                                                    "Imagens (*.png *.xpm *.jpg)"
                                                    );
    if(!photosDir.isEmpty()){

        //Adicionar Foto
        //ListAlbuns::createPhoto(AlbumName, PageName);
        //Actualizar GUI

        //Apresenta Mensagem de confirmação
        QMessageBox *msg = new QMessageBox(QMessageBox::Information,"Fotos Adicionadas", "Fotos adicionadas com sucesso!",
                                              QMessageBox::Ok,this);

        msg->exec();
    }
}
