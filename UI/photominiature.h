#ifndef PHOTOMINIATURE_H
#define PHOTOMINIATURE_H

#include <QWidget>

class Foto;

namespace Ui {
class PhotoMiniature;
}

class PhotoMiniature : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoMiniature(Foto* photo, QWidget *parent = 0);
    ~PhotoMiniature();

    Foto* getPhoto();

private:
    Ui::PhotoMiniature *ui;

    Foto* thisPhoto;

};

#endif // PHOTOMINIATURE_H
