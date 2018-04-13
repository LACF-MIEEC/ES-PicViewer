#ifndef MANAGEPEOPLE_H
#define MANAGEPEOPLE_H

#include <QWidget>
#include <QMessageBox>
#include <QDateEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>

#include "addpersondialog.h"

#include "CustomClasses/listapessoas.h"

class Pessoa;

namespace Ui {
class ManagePeople;
}

class ManagePeople : public QWidget
{
    Q_OBJECT

public:
    explicit ManagePeople(GestorBD *gestor, QWidget *parent = 0);
    ~ManagePeople();

    void addItemPeopleList(Pessoa *newItem);

private slots:
    void on_Voltar_clicked();

    void on_DelPerson_clicked();

    void on_AddPerson_clicked();

    void addPerson(AddPersonDialog *Dialog);

    void on_PeopleList_itemClicked(QListWidgetItem *item);

private:
    Ui::ManagePeople *ui;

    ListaPessoas* aListaPessoas;
    GestorBD*   oGestor;

};

#endif // MANAGEPEOPLE_H
