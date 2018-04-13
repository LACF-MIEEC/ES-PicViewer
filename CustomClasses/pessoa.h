#ifndef PESSOA_H
#define PESSOA_H

#include <QVector>
#include <QString>
#include <QDate>
#include <QDir>
#include <QDebug>

#include "gestorbd.h"

/*!
 * \brief Classe representativa de uma %Pessoa na ótica do utilizador.
 *
 * Contém as Fotos associadas e as características associadas à representação de uma %Pessoa.
 */

class Pessoa
{
public:

    ////////////////////////////////////////////////
    /*!
     * \brief Construtor
     * \param Estrutura PersonParam
     */
    Pessoa(PersonParam atributes);

    /*!
     * \brief Destrutor
     */
    ~Pessoa();


    //----------------Get Atributes----------------//

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve ID da %Pessoa.
     * \return ID da %Pessoa.
     */
    int getID();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Nome da %Pessoa
     * \return Nome da %Pessoa
     */
    QString getName();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve data de de Nascimento da %Pessoa
     * \return Data de Nascimento da %Pessoa
     */
    QDate getBirth();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Género da Pessoa
     * \return Género da Pessoa
     */
    gender getGender();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Relação da Pessoa
     * \return Relação da Pessoa
     */
    QString getBond();

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve pessoas associadas á %Foto
     * \return Ponteiro apra vetor de classes Foto
     */
    QVector<Foto*> *getPhotos();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve lista de Pessoas
     * \return Ponteiro para a classe ListaPessoas
     */
    ListaPessoas* parent();

    /* ATTACHMENTS NOT YET IMPLEMENTED
    int acceptPhoto(Foto* photo);
    */
    /* REMOVE NOT YET IMPLEMENTED
    int removePhoto(Foto* photo);
    */

private:

    int ID;
    QString Name;
    QDate Birth;
    gender Gender;
    QString Bond;

    ListaPessoas *Parent;
    GestorBD* oGestor;
    QVector<Foto*> *Photos;
};

#endif // PESSOA_H
