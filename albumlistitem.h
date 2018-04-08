#ifndef ALBUMLISTITEM_H
#define ALBUMLISTITEM_H

#include <QWidget>

namespace Ui {
class AlbumListItem;
}

class AlbumListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListItem(QWidget *parent = 0, QString Text = NULL);
    ~AlbumListItem();

private:
    Ui::AlbumListItem *ui;
};

#endif // ALBUMLISTITEM_H
