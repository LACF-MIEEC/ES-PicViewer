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
    explicit PhotoDisplay(const QImage &newImage, QWidget *parent = 0);
    ~PhotoDisplay();


private slots:
    void on_Return_clicked();

private:
    Ui::PhotoDisplay *ui;

    QImage Image;
};

#endif // PHOTODISPLAY_H
