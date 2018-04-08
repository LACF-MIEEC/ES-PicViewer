#ifndef MANAGEPEOPLE_H
#define MANAGEPEOPLE_H

#include <QWidget>

namespace Ui {
class ManagePeople;
}

class ManagePeople : public QWidget
{
    Q_OBJECT

public:
    explicit ManagePeople(QWidget *parent = 0);
    ~ManagePeople();

    void addItemPeopleList(QString ItemName);

private slots:
    void on_Voltar_clicked();

private:
    Ui::ManagePeople *ui;
};

#endif // MANAGEPEOPLE_H
