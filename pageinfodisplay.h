#ifndef PAGEINFODISPLAY_H
#define PAGEINFODISPLAY_H

#include <QWidget>

namespace Ui {
class PageInfoDisplay;
}

class PageInfoDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PageInfoDisplay(QWidget *parent = 0);
    ~PageInfoDisplay();

private:
    Ui::PageInfoDisplay *ui;
};

#endif // PAGEINFODISPLAY_H
