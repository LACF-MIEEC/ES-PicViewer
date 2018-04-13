#ifndef ADDPAGEDIALOG_H
#define ADDPAGEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "CustomClasses/paramstructs.h"

namespace Ui {
class AddPageDialog;
}

class AddPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPageDialog(pageType_t tipo, QWidget *parent = 0);
    ~AddPageDialog();

private slots:


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


signals:
    void pageAccepted(AddPageDialog *Dialog);

private:
    Ui::AddPageDialog *ui;
};

#endif // ADDPAGEDIALOG_H
