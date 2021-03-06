#ifndef ALBUMLISTITEM_H
#define ALBUMLISTITEM_H

#include <QWidget>
class Album;

namespace Ui {
class AlbumListItem;
}

class AlbumListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListItem(Album *album = 0,QWidget *parent = 0);
    ~AlbumListItem();

    Album* getAlbum();

private:
    Ui::AlbumListItem *ui;
    Album* thisAlbum;
};

#endif // ALBUMLISTITEM_H
