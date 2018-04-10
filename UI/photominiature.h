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
    explicit PhotoMiniature(int *FotoNum, QWidget *parent = 0);
    ~PhotoMiniature();
    int Foto;
private:
    Ui::PhotoMiniature *ui;


};

#endif // PHOTOMINIATURE_H
