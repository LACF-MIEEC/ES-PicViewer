#ifndef ADDASSOCIATIONDIALOG_H
#define ADDASSOCIATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddAssociationDialog;
}

class AddAssociationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAssociationDialog(QWidget *parent = 0);

    ~AddAssociationDialog();

private:
    Ui::AddAssociationDialog *ui;
};

#endif // ADDASSOCIATIONDIALOG_H
