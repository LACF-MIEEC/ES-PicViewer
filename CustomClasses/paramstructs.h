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

////////////////////////////////////////////////
/*!
 * \brief Estrututa que contém os atributos de Foto
 */
struct PhotoParam{
    int ID;
    QDir Path;
    Pagina* Parent;
    int ParentID;
    GestorBD* Gestor;
};

////////////////////////////////////////////////
/*!
 * \brief Tipos de página
 */
enum pageType_t : short int { viagem, festa, coisaPessoa, outro };

////////////////////////////////////////////////
/*!
 * \brief Estrutura que contém os atributos de Pagina
 */
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

////////////////////////////////////////////////
/*!
 * \brief Estrutura que contém os atributos de Album
 */
struct AlbumParam{
    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;
    ListaAlbuns* Parent =0;
    GestorBD* Gestor =0;
};

////////////////////////////////////////////////
/*!
 * \brief Género
 */
enum gender :short int {feminino, masculino};

////////////////////////////////////////////////
/*!
 * \brief Estrutura que contém os atributos de Pessoa
 */
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
