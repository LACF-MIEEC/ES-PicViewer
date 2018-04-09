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
    // Chamar funções

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

void MainWindow::on_AlbumList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString NomeAlbum, NomePagina="";

    if(!current->parent()){ //Se current Album

        current->setExpanded(true);
        //Alterar restantes sitios da frame onde o album ou as suas caracteristicas são definidas
        NomeAlbum = ui->AlbumList->itemWidget(current,0)->findChild<QLabel*>("Text")->text();


        ui->Title->setText(QString(NomeAlbum));
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
        NomeAlbum = ui->AlbumList->itemWidget(current->parent(),0)->findChild<QLabel*>("Text")->text();
        NomePagina=  ui->AlbumList->itemWidget(current,0)->findChild<QLabel*>("Text")->text();

        ui->Title->setText(QString(NomeAlbum + " : " + NomePagina));
        //-------------
        //Colocar Fotos no Display

        QTableWidgetItem *Photos;

        //Aceder a objecto página
        //obter path das fotos

        QStringList PhotoPath;

        PhotoPath << ":/Photos/bin/Images/Login_Background.png" << ":/Photos/bin/Images/logo.png";


        //obter pessoas das fotos
        //???????????

        ui->PhotoDisplay->setRowCount(PhotoPath.size()/ui->PhotoDisplay->columnCount()+1);
        int row=0; int column=0;

        for(int i=0;i<PhotoPath.size();i++){

            Photos = new QTableWidgetItem(QIcon(QPixmap(PhotoPath.at(i)).scaled(ui->PhotoDisplay->iconSize(),Qt::KeepAspectRatio)),QString(""));

            Photos->setSizeHint(ui->PhotoDisplay->iconSize());

            ui->PhotoDisplay->setItem(row,column,Photos);

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

void MainWindow::addItemPeopleList(QString ItemName){

    ui->PeopleList->addItem(new QListWidgetItem(QIcon(":/Icons/bin/Icons/People.png"),ItemName));

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

    toDelete->~QListWidgetItem();
}
