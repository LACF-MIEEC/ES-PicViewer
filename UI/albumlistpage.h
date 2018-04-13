#ifndef ALBUMLISTPAGE_H
#define ALBUMLISTPAGE_H

#include <QWidget>

class Pagina;
namespace Ui {
class AlbumListPage;
}

class AlbumListPage : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListPage(QString text, Pagina *page = 0, QWidget *parent = 0);
    ~AlbumListPage();

    Pagina* getPage();

private:
    Ui::AlbumListPage *ui;
    Pagina* thisPage;
};

#endif // ALBUMLISTPAGE_H
