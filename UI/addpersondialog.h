#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QWidget>
#include <QMessageBox>

class Album;
class Pagina;
class Pessoa;
class Foto;

class GestorBD;
class ListaAlbuns;
class ListaPessoas;

struct PhotoParam;
struct PageParam;
struct AlbumParam;
struct PersonParam;

enum pageType_t:short int;
enum gender: short int;

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = 0);
    ~AddPersonDialog();

signals:
    void personAccepted(AddPersonDialog *Dialog);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AddPersonDialog *ui;
};

#endif // ADDPERSONDIALOG_H
