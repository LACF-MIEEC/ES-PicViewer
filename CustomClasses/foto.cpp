#include "foto.h"

Foto::Foto(int id, QDir Dir, Pagina* parent, GestorBD* gestor)
{
    FotoID      = ID;
    Directory   = Dir;
    Parent      = parent;
}
