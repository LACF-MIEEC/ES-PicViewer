#ifndef LISTAPESSOAS_H
#define LISTAPESSOAS_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "pessoa.h"

/*!
 * \brief Classe responsável por gerir objetos da classe %Pessoa e as suas associações com fotos.
 *
 * Como tal é também responsável por efetuar a pesquisa de %Foto por Pessoa associada.
 */
class ListaPessoas
{
public:
    /*!
     * \brief Construtor
     * \param gestor - Ponteiro para a classe GestorBD.
     */
    ListaPessoas(GestorBD* gestor=0);

    /*!
     *\brief Destrutor
     */
    ~ListaPessoas();
    //----------------Get Atributes----------------//

    /*!
     * \brief  Devolve Todas as Pessoas.
     * \return Ponteiro para vetor de classes Pessoa.
     */
    QVector<Pessoa*> getPeople();

    //-------------------Create--------------------//

    /*!
     * \brief Cria nova Pessoa
     *
     * Cria nova pessoa com os atributos definidos em atributes.
     * \param atributes - Estrutura PersonParam.
     * \return Ponteiro para a classe Pessoa.
     */
    Pessoa* createPerson(PersonParam atributes);

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotosByPerson(QString name);
    */
    /* REMOVE AND ATTACHMENTS NOT YET IMPLEMENTED
    int deletePerson(Pessoa*);

    int attachPerson(Pessoa* person, Foto* foto);
    int dettachPerson(Pessoa* person, Foto* foto);
    */


private:

    QVector<int> allocatedPeopleID;
    int maxPeopleID;

    int generateID(QVector<int> &allocatedID, int &maxID);
    int genPersonID();

    QVector<Pessoa*> *People;
    GestorBD* oGestor;
};

#endif // LISTAPESSOAS_H
