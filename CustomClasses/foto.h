#ifndef FOTO_H
#define FOTO_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "gestorbd.h"
//#include "listapessoas.h"
class ListaPessoas;
////////////////////////////////////////////////
/*!
 * \brief Classe que representa uma %Foto.
 *
 * Contém a diretoria da imagem.
 */
class Foto
{
public:

    ////////////////////////////////////////////////
    /*!
     * \brief Construtor
     * \param atributes - Estrutura PhotoParam
     */
    Foto(PhotoParam atributes);
  
    /*!
     *\brief Destrutor
     */
    ~Foto();


    //----------------Get Atributes----------------//

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve ID da %Foto
     * \return ID da  %Foto
     */
    int getID();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve caminho do ficheiro %Foto
     * \return caminho do ficheiro %Foto
     */
    QDir getPath();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Pessoas associadas à %Foto
     * \return Ponteiro para o vetor de classes Pessoa
     */
    QVector<Pessoa *> *getPeople();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Página da %Foto
     * \return Ponteiro para a classe Pagina
     */
    Pagina* parent();

    /*ASSOCIATIONS NOT YET IMPLEMENTED
    int acceptPerson(Pessoa* Person);
    int removePerson(Pessoa* Person);
    */

private:

    int ID;
    QDir Path;
    QVector<Pessoa*> *People;

    ListaPessoas* PeopleList;//Como se lá chega?????????
    GestorBD* oGestor;
    Pagina* Parent;

};

#endif // FOTO_H
