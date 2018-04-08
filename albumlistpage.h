#ifndef ALBUMLISTPAGE_H
#define ALBUMLISTPAGE_H

#include <QWidget>

namespace Ui {
class AlbumListPage;
}

class AlbumListPage : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListPage(QWidget *parent = 0, QString Text = NULL);
    ~AlbumListPage();

private:
    Ui::AlbumListPage *ui;
};

#endif // ALBUMLISTPAGE_H
