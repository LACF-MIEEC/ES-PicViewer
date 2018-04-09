#ifndef PHOTOMINIATURE_H
#define PHOTOMINIATURE_H

#include <QWidget>

namespace Ui {
class PhotoMiniature;
}

class PhotoMiniature : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoMiniature(QWidget *parent = 0);
    ~PhotoMiniature();

private:
    Ui::PhotoMiniature *ui;
};

#endif // PHOTOMINIATURE_H
