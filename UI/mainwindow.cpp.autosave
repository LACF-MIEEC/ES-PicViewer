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

    QMessageBox* msg;

    if(!aListaAlbuns->loadAll()){
        msg = new QMessageBox(QMessageBox::Warning,"Foto Inexistente", "A Foto que selecionou não existe!",
                              QMessageBox::Ok);
        msg->exec();
        msg->deleteLater();
    }

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

    QStringList PagesNames;

    QVector<Pagina*>* AlbumPages=newItem->getPages();

    for(int i=0;i<newItem->getPages()->size();i++){
        //Na Arvore pagina apresenta a primeira palavra da descrição
        PagesNames.append(AlbumPages->at(i)->getDescription().trimmed().split(" ").at(0));
    }

    QTreeWidgetItem *TreeItem = new QTreeWidgetItem(ui->AlbumList);

    AlbumListItem *ItemWidget = new AlbumListItem(newItem);

    //Adicionar Crianças
    QTreeWidgetItem *ChildItem;
    AlbumListPage *ChildWidget;

    for(int i=0; i < PagesNames.size() ;i++){
        ChildItem= new QTreeWidgetItem(TreeItem);
        ChildWidget= new AlbumListPage(QString(PagesNames.at(i)),AlbumPages->at(i));

        ui->AlbumList->setItemWidget(ChildItem,0,ChildWidget);
        ChildItem->setSizeHint(0,ChildWidget->sizeHint());
    }
    TreeItem->setSizeHint(0,ItemWidget->sizeHint());
    ui->AlbumList->setItemWidget(TreeItem,0,ItemWidget);

}

void MainWindow::addItemAlbumTree(Pagina* newItem){

    QTreeWidgetItem *ChildItem= new QTreeWidgetItem(ui->AlbumList->currentItem());
    AlbumListPage *ChildWidget= new AlbumListPage(newItem->getDescription().trimmed().split(" ").at(0),newItem);

    ui->AlbumList->setItemWidget(ChildItem,0,ChildWidget);
    ChildItem->setSizeHint(0,ChildWidget->sizeHint());
}

void MainWindow::addItemPeopleList(QString ItemName){

    ui->PeopleList->addItem(new QListWidgetItem(QIcon(":/Icons/bin/Icons/People.png"),ItemName));

}

void MainWindow::on_AlbumList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString AlbumName, PageName="";
    AlbumListItem* AlbumItem;

    if(!current->parent()){ //Se current Album

        current->setExpanded(true);

        ui->Info->removeItem(1);
        //Alterar restantes sitios da frame onde o album ou as suas caracteristicas são definidas

        AlbumItem = (AlbumListItem*)ui->AlbumList->itemWidget(current,0);
        SelectedAlbum = AlbumItem->getAlbum();
        SelectedPage  = 0;

        AlbumName=SelectedAlbum->getName();
        //
        //      ACTUALIZAR UI
        //
        if(!previous){
             ui->Info->addItem(wAlbumInfo,"Informações do Álbum");
        }
        wAlbumInfo->findChild<QLabel*>("Name")->setText(AlbumName);
        switch(SelectedAlbum->getPageType()){
        case viagem:
            wAlbumInfo->findChild<QLabel*>("Type")->setText("Viagem");
            break;
        case coisaPessoa:
            wAlbumInfo->findChild<QLabel*>("Type")->setText("Coisa ou Pessoa");
            break;
        case festa:
            wAlbumInfo->findChild<QLabel*>("Type")->setText("Festa");
            break;
        case outro:
            wAlbumInfo->findChild<QLabel*>("Type")->setText("Outro");
            break;

        }
        wAlbumInfo->findChild<QLabel*>("Path")->setText(SelectedAlbum->getPath().path());
        wAlbumInfo->findChild<QLabel*>("Description")->setText(SelectedAlbum->getDescription());

        ui->Title->setText(QString(AlbumName));
        //-------------
        //Retirar Fotos do display
        ui->PhotoDisplay->setRowCount(0);     
        //
        //
        //
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
    //Se current Página
    else{
        //Procurar o album pertencente
        AlbumListPage* PageItem;
        AlbumItem = (AlbumListItem*)ui->AlbumList->itemWidget(current->parent(),0);
        SelectedAlbum = AlbumItem->getAlbum();

        PageItem = (AlbumListPage*)ui->AlbumList->itemWidget(current,0);
        SelectedPage  = PageItem->getPage();

        //Alterar restantes sitios da frame onde o album/pagina ou as suas caracteristicas são definidas
        AlbumName = SelectedAlbum->getName();
        PageName  = ui->AlbumList->itemWidget(current,0)->findChild<QLabel*>("Text")->text();

        ui->Title->setText(QString(AlbumName + " : " + PageName));

        // Fotos da Página
        QVector<Foto*>* PagePhotos=SelectedPage->getPhotos();

        ui->PhotoDisplay->setRowCount(PagePhotos->size()/ui->PhotoDisplay->columnCount()+1);
        int row=0; int column=0;


        QTableWidgetItem *Item;
        PhotoMiniature *Miniature;

        for(int i=0;i<PagePhotos->size();i++){

            QImageReader reader(PagePhotos->at(i)->getPath().path());
            reader.setAutoTransform(true);
            const QImage newImage = reader.read();
            if (newImage.isNull()) {
                QMessageBox::information(this, QApplication::applicationDisplayName(),
                                             tr("Cannot load %1: %2")
                                             .arg(QDir::toNativeSeparators(PagePhotos->at(i)->getPath().path()), reader.errorString()));
                return;
            }

            Miniature = new PhotoMiniature(PagePhotos->at(i));

            Miniature->findChild<QLabel*>("Photo")->setPixmap(QPixmap::fromImage(newImage).scaled(
                                                                  QSize(ui->PhotoDisplay->horizontalHeader()->sectionSize(0),ui->PhotoDisplay->horizontalHeader()->sectionSize(0))
                                                              ,Qt::KeepAspectRatio));
            Miniature->findChild<QLabel*>("Photo")->adjustSize();

            Item = new QTableWidgetItem();

            Item->setSizeHint(QSize(ui->PhotoDisplay->horizontalHeader()->sectionSize(0),ui->PhotoDisplay->horizontalHeader()->sectionSize(0)));

            ui->PhotoDisplay->setItem(row,column,Item);

            ui->PhotoDisplay->setCellWidget(row,column,Miniature);

            column++;
            if(column==ui->PhotoDisplay->columnCount()){
                column=0;
                row++;
            }
        }
        if(previous){
            if(!previous->parent()){ //Se Anterior for Album
                ui->Info->addItem(wPageInfo,"Informações da Página");
            }
        }

        wPageInfo->findChild<QLabel*>("Description")->setText(SelectedPage->getDescription());

        switch(SelectedPage->getType()){
        case viagem:
            wPageInfo->findChild<QLabel*>("StartDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("EndDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("PartyType")->setVisible(false);

            wPageInfo->findChild<QLabel*>("label_Date")->setVisible(true);
            wPageInfo->findChild<QLabel*>("label_EndDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("label_PartyType")->setVisible(false);

            wPageInfo->findChild<QLabel*>("label_Date")->setText("Data de Inicio:");

            wPageInfo->findChild<QLabel*>("StartDate")->setText(SelectedPage->getStartDate().toString(Qt::ISODate));
            wPageInfo->findChild<QLabel*>("EndDate")->setText(SelectedPage->getEndDate().toString(Qt::ISODate));
            break;
        case coisaPessoa:
            wPageInfo->findChild<QLabel*>("StartDate")->setVisible(false);
            wPageInfo->findChild<QLabel*>("EndDate")->setVisible(false);
            wPageInfo->findChild<QLabel*>("PartyType")->setVisible(false);

            wPageInfo->findChild<QLabel*>("label_Date")->setVisible(false);
            wPageInfo->findChild<QLabel*>("label_EndDate")->setVisible(false);
            wPageInfo->findChild<QLabel*>("label_PartyType")->setVisible(false);

            break;
        case festa:
            wPageInfo->findChild<QLabel*>("StartDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("EndDate")->setVisible(false);
            wPageInfo->findChild<QLabel*>("PartyType")->setVisible(true);

            wPageInfo->findChild<QLabel*>("label_Date")->setVisible(true);
            wPageInfo->findChild<QLabel*>("label_EndDate")->setVisible(false);
            wPageInfo->findChild<QLabel*>("label_PartyType")->setVisible(true);

            wPageInfo->findChild<QLabel*>("label_Date")->setText("Data:");

            wPageInfo->findChild<QLabel*>("StartDate")->setText(SelectedPage->getStartDate().toString(Qt::ISODate));
            wPageInfo->findChild<QLabel*>("PartyType")->setText(SelectedPage->getPartyType());
            break;
        case outro:
            wPageInfo->findChild<QLabel*>("StartDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("EndDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("PartyType")->setVisible(false);

            wPageInfo->findChild<QLabel*>("label_Date")->setVisible(true);
            wPageInfo->findChild<QLabel*>("label_EndDate")->setVisible(true);
            wPageInfo->findChild<QLabel*>("label_PartyType")->setVisible(false);

            wPageInfo->findChild<QLabel*>("label_Date")->setText("Data de Inicio:");

            wPageInfo->findChild<QLabel*>("StartDate")->setText(SelectedPage->getStartDate().toString(Qt::ISODate));
            wPageInfo->findChild<QLabel*>("EndDate")->setText(SelectedPage->getEndDate().toString(Qt::ISODate));
            break;
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
            return;
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
           return;
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

    int PhotoCounter=0;

    if(!photosPath.isEmpty()){

        PhotoParam atributes;
        //Verificar se cada uma das fotos existe
        for(int i=0;i<photosPath.size();i++){
            photoDir.setPath(photosPath.at(i));
            if(!photoDir.exists(photosPath.at(i))){
                msg = new QMessageBox(QMessageBox::Warning,"Foto Inexistente", "A Foto que selecionou não existe!",
                                      QMessageBox::Ok,this);
                msg->exec();
                msg->deleteLater();
            }
            else{
                //Adicionar Foto
                atributes.Gestor=oGestor;
                atributes.Parent=SelectedPage;
                atributes.ParentID=SelectedPage->getID();
                atributes.Path = photosPath.at(i);

                if(!aListaAlbuns->createPhoto(atributes,SelectedPage, SelectedAlbum)){
                    msg = new QMessageBox(QMessageBox::Warning,"Erro", "Falha ao Criar a Foto!",
                                          QMessageBox::Ok,this);
                    msg->exec();
                    msg->deleteLater();
                    break;
                }

                PhotoCounter++;
            }
        }
        //updateGUI();

        if(PhotoCounter==0)
            msg = new QMessageBox(QMessageBox::Information,"Fotos Inexistentes", "As Fotos que selecionou não existem!",
                              QMessageBox::Ok,this);
        else
            msg = new QMessageBox(QMessageBox::Information,"Fotos Adicionadas", QString(QString::number(PhotoCounter)+" Fotos adicionadas com sucesso!"),
                                  QMessageBox::Ok,this);

        msg->exec();
        msg->deleteLater();
    }

}

void MainWindow::on_PhotoDisplay_cellDoubleClicked(int row, int column)
{
    PhotoMiniature* CurrentPhoto;
    CurrentPhoto= (PhotoMiniature*)ui->PhotoDisplay->cellWidget(row,column);

    QImageReader reader(CurrentPhoto->getPhoto()->getPath().path());
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    PhotoDisplay *Display = new PhotoDisplay(newImage,this);

    Display->show();
}
