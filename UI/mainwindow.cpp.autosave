#include "mainwindow.h"
#include "ui_mainwindow.h"

Setup::RunStates RunMode;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Title->setText("PicViewer - Bem Vindo!!");
    this->setWindowState(Qt::WindowMaximized);

    oGestor      = new GestorBD(DBPath.path());
    aListaAlbuns = new ListaAlbuns(oGestor);

    wPeople = new ManagePeople(oGestor);

    aListaAlbuns->loadAll();

    for(int i=0;i<aListaAlbuns->getAlbums()->size();i++){
        addItemAlbumTree(aListaAlbuns->getAlbums()->at(i));
    }
    ui->AlbumList->collapseAll();

    ui->PhotoDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->PhotoDisplay->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PhotoDisplay->setColumnCount(4);

    wAlbumInfo= new AlbumInfoDisplay();
    wPageInfo= new PageInfoDisplay();

    wAlbumInfo->resize(ui->Info->sizeHint());
    wPageInfo->resize(ui->Info->sizeHint());

    ui->Info->removeItem(0);
    ui->Info->removeItem(0);
    ui->Info->addItem(wAlbumInfo,"Informações do Álbum");
    ui->Info->addItem(wPageInfo,"Informações da Página");


}

MainWindow::~MainWindow()
{
    /*
        Serão executadas as rotinas de fecho aqui.
        Talvez Chamar uma funçao de fecho,
            para engobar outras opções de fecho p.e. botão [X].
    */
    delete oGestor;
    delete aListaAlbuns;
    delete ui;
}

void MainWindow::addItemAlbumTree(Album* newItem)
{
    QString ItemName(newItem->getName());
    QStringList PageName;

    for(int i=0;i<newItem->getPages()->size();i++){
        //Na Arvore pagina apresenta a primeira palavra da descrição
        PageName.append(newItem->getPages()->at(i)->getDescription().trimmed().split(" ").at(0));
    }

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

void MainWindow::addItemAlbumTree(Pagina* newItem){

    QTreeWidgetItem *ChildItem= new QTreeWidgetItem(ui->AlbumList->currentItem());
    AlbumListPage *ChildWidget= new AlbumListPage(NULL,newItem->getDescription().trimmed().split(" ").at(0));

    ui->AlbumList->setItemWidget(ChildItem,0,ChildWidget);
    ChildItem->setSizeHint(0,ChildWidget->sizeHint());
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
        QVector<int*> PhotoID;

        PhotoPath << ":/Photos/bin/Images/Login_Background.png" << ":/Photos/bin/Images/logo.png";
        PhotoID.fill(0,3);

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

            Miniature = new PhotoMiniature(PhotoID.at(i));

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
        AlbumParam atributes;

        atributes.Name = Dialog->findChild<QLineEdit*>("Name")->text();
        atributes.Description = Dialog->findChild<QPlainTextEdit*>("Description")->toPlainText();
        QString Type = Dialog->findChild<QComboBox*>("Type")->currentText();
        atributes.Path.setPath(Dialog->findChild<QLineEdit*>("Directory")->text());

        if(Type.operator ==("Viagem"))
            atributes.PageType=viagem;
        else if(Type.operator ==("Festa"))
            atributes.PageType=festa;
        else if(Type.operator ==("Coisa ou Pessoa"))
            atributes.PageType=coisaPessoa;
        else if(Type.operator ==("Outro"))
            atributes.PageType=outro;

        atributes.Parent = aListaAlbuns;
        atributes.Gestor = oGestor;

        Album* newAlbum=aListaAlbuns->createAlbum(atributes);
        QMessageBox *msg;
        if(newAlbum==nullptr){
            msg = new QMessageBox(QMessageBox::Warning,"Erro", "Falha ao criar Album!",
                                                 QMessageBox::Ok,this);
        }
        msg = new QMessageBox(QMessageBox::Information,"Album Criado", "O Álbum foi criado com sucesso!",
                                             QMessageBox::Ok,this);
        addItemAlbumTree(newAlbum);

        msg->exec();
        msg->deleteLater();
        Dialog->close();
        Dialog->deleteLater();
}

void MainWindow::on_AddPage_clicked()
{
    if(!ui->AlbumList->currentItem()){
        QMessageBox *msg = new QMessageBox(QMessageBox::Warning,"Aviso", "Selecione um album para adicionar a pagina!",
                                              QMessageBox::Ok,this);
        msg->exec();
        return;
    }

    //Altera caixa de Dialogo para os detalhes corresponderem ao tipo de Página

    if(!ui->AlbumList->currentItem()->parent()){ //Se estiver o Album Seleccionado
        SelectedAlbum = aListaAlbuns->getAlbums()->at(ui->AlbumList->currentIndex().row());
    }
    else{ //Caso seja um página procurar o album pertencente
        SelectedAlbum = aListaAlbuns->getAlbums()->at(ui->AlbumList->indexOfTopLevelItem(ui->AlbumList->currentItem()));
    }

    AddPageDialog *Dialog = new AddPageDialog(SelectedAlbum->getPageType());

    connect(Dialog,SIGNAL(pageAccepted(AddPageDialog*)), this, SLOT(addPage(AddPageDialog*)));
    Dialog->show();
}

void MainWindow::addPage(AddPageDialog *Dialog){

       PageParam atributes;
       //Criar a Página e Actualizar a interface
       atributes.Description= Dialog->findChild<QPlainTextEdit*>("Description")->toPlainText();

       //Alguns destes podem não se aplicar,  dependendo do tipo de página
       atributes.StartDate = Dialog->findChild<QDateEdit*>("Date")->date();
       atributes.EndDate = Dialog->findChild<QDateEdit*>("DateEnd")->date();
       atributes.PartyType = Dialog->findChild<QLineEdit*>("Type")->text();

       atributes.Gestor=oGestor;
       atributes.Parent=SelectedAlbum;
       atributes.ParentID=SelectedAlbum->getID();
       atributes.Path=SelectedAlbum->getPath();
       atributes.Type=SelectedAlbum->getPageType();

       Pagina* newPage=aListaAlbuns->createPage(atributes,SelectedAlbum);
       QMessageBox *msg;
       if(newPage==nullptr){
           msg = new QMessageBox(QMessageBox::Warning,"Erro", "Falha ao criar Pagina!",
                                                QMessageBox::Ok,this);
       }
       addItemAlbumTree(newPage);

       msg = new QMessageBox(QMessageBox::Information,"Página Criada", "A Página foi criada com sucesso!",
                                             QMessageBox::Ok,this);

       msg->exec();
       Dialog->close();
       Dialog->deleteLater();
       msg->deleteLater();
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
    QStringList photosPath = QFileDialog::getOpenFileNames(this, "Selecione uma ou mais Fotos",
                                                    QDir::homePath(),
                                                    "Imagens (*.png *.xpm *.jpg)"
    );

    QMessageBox *msg;
    QDir photoDir;

    if(!photosPath.isEmpty()){

        //Verificar se cada uma das fotos existe
        for(int i=0;i<photosPath.size();i++){
            photoDir.setPath(photosPath.at(i));
            if(!photoDir.exists()){
                msg = new QMessageBox(QMessageBox::Warning,"Foto Inexistente", "A Fotos que selecionou não existe!",
                                                      QMessageBox::Ok,this);
                msg->exec();
                msg->deleteLater();
            }

            //Adicionar Foto
            aListaAlbuns->createPhoto(atributes,SelectedAlbum, SelectedPage);

        }

        //Adicionar Foto
        //ListAlbuns::createPhoto(AlbumName, PageName);
        //Actualizar GUI

        //Apresenta Mensagem de confirmação
        msg = new QMessageBox(QMessageBox::Information,"Fotos Adicionadas", "Fotos adicionadas com sucesso!",
                                              QMessageBox::Ok,this);

        msg->exec();
        msg->deleteLater();
    }

}

void MainWindow::on_PhotoDisplay_cellDoubleClicked(int row, int column)
{
    //ui->PhotoDisplay->cellWidget(row,column)->findChild<int>("Foto");

    //qDebug() << ui->PhotoDisplay->cellWidget(row,column)->;

    QImageReader reader(":/Photos/bin/Images/alegria.png");
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    PhotoDisplay *Display = new PhotoDisplay(newImage,this);

    Display->show();
}
