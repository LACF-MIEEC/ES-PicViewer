#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QListWidget>
#include <QDialog>
#include <QApplication>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QList>
#include <QLineEdit>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QImageReader>
#include <QVector>
#include <QDebug>

#include "albumlistitem.h"
#include "albumlistpage.h"
#include "managepeople.h"
#include "addassociationdialog.h"
#include "albuminfodisplay.h"
#include "addalbumdialog.h"
#include "addpagedialog.h"
#include "photodisplay.h"
#include "photominiature.h"
#include "pageinfodisplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void addItemAlbumTree(QString ItemName,QStringList PageName);

    void addItemPeopleList(QString ItemName);


private slots:
    void on_AlbumList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_Exit_triggered();

    void on_ManagePeople_clicked();

    void on_AddAssociation_clicked();

    void on_RemoveAssociation_clicked();

    void on_AddAlbum_clicked();

    void on_AddPage_clicked();

    void addAlbum(AddAlbumDialog *Dialog);

    void addPage(AddPageDialog *Dialog);

    void on_AddPhoto_clicked();

    void on_PhotoDisplay_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    ManagePeople *wPeople;

    //QVector<Fotos*> Vector;

};

#endif // MAINWINDOW_H
