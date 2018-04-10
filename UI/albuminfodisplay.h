#ifndef ALBUMINFODISPLAY_H
#define ALBUMINFODISPLAY_H

#include <QWidget>

namespace Ui {
class AlbumInfoDisplay;
}

class AlbumInfoDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumInfoDisplay(QWidget *parent = 0);
    ~AlbumInfoDisplay();

private:
    Ui::AlbumInfoDisplay *ui;
};

#endif // ALBUMINFODISPLAY_H
