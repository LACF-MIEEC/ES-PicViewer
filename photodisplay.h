#ifndef PHOTODISPLAY_H
#define PHOTODISPLAY_H

#include <QWidget>

namespace Ui {
class PhotoDisplay;
}

class PhotoDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoDisplay(QWidget *parent = 0);
    ~PhotoDisplay();

private:
    Ui::PhotoDisplay *ui;
};

#endif // PHOTODISPLAY_H
