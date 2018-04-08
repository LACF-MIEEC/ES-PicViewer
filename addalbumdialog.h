#ifndef ADDALBUMDIALOG_H
#define ADDALBUMDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class AddAlbumDialog;
}

class AddAlbumDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddAlbumDialog(QWidget *parent = 0);
    ~AddAlbumDialog();

private slots:

    void on_BrowseButton_clicked();

    void on_Result_accepted();

private:
    Ui::AddAlbumDialog *ui;
};

#endif // ADDALBUMDIALOG_H
