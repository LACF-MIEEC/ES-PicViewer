#ifndef FOTO_H
#define FOTO_H

#include <string>
#include <QVector>

//#include "listaalbuns.h"
class ListaAlbuns;

//#include "gestorbd.h"
class GestorBD;

//#include "pessoa.h"
class Pessoa;

//#include "pagina.h"
class Pagina;

struct FotoParams{
    int fotoID;
    //...
};

class Foto
{
public:
    Foto(FotoParams params);
    ~Foto();

    int deleteSelf(); // Remover-se da base de dados, eliminar ficheiro

    std::string getPath();
    int getID();

    Pagina* parent();


    int acceptPerson(Pessoa* person);
    int removePerson(Pessoa* person);
    QVector<Pessoa*> getPeople();
private:

    int fotoID;

    std::string directoria; //ingles? assim é como está no SAD

    QVector<Pessoa*> people;

    ListaAlbuns* aListaAlbuns;
    GestorBD* oGestor;
    Pagina* parent;
};

#endif // FOTO_H
