#include "pagina.h"

Pagina::Pagina(PaginaParams params)
{
    pageID = params.pageID;
    // atributos comuns a todos os tipos
}



// ------------- VIAGEM ----------------------------

PaginaViagem::PaginaViagem(PaginaParams params) : Pagina(params)
{
    //...
}

pageType_t PaginaViagem::getType()
{
    return viagem;
}

std::string PaginaViagem::createFolderName(){
    std::string folderName = "insert name here";
    return folderName;
}
