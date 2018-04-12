#ifndef PARAMSTRUCTS_H
#define PARAMSTRUCTS_H

#include <QString>
#include <QDir>
#include <QDate>

class Album;
class Pagina;
class Pessoa;
class Foto;

class GestorBD;
class ListaAlbuns;
class ListaPessoas;

struct PhotoParam{
    int ID;
    QDir Path;
    Pagina* Parent;
    int ParentID;
    GestorBD* Gestor;
};

enum pageType_t : short int { viagem, festa, coisaPessoa, outro };

struct PageParam{
  int ID;
  pageType_t Type;
  QString Description;
  QDir Path;
  QDate StartDate;
  QDate EndDate;
  QString PartyType;
  Album* Parent=0;
  int   ParentID;
  GestorBD* Gestor=0;
};


struct AlbumParam{
    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;
    ListaAlbuns* Parent =0;
    GestorBD* Gestor =0;
};

enum gender :short int {feminino, masculino};

struct PersonParam{
    int ID;
    QString Name;
    QDate Birth;
    gender Gender;
    QString Bond;
    ListaPessoas* Parent;
    GestorBD* Gestor;
};

#endif // PARAMSTRUCTS_H
