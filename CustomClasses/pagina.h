#ifndef PAGINA_H
#define PAGINA_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "foto.h"

/*!
 * \brief Classe representativa de uma página na ótica do utilizador.
 *
 * Contém as Fotos e as características associadas à representação de uma página.
 */
class Pagina
{
public:

    /*!
     * \brief Construtor
     * \param atributes - Estrutura PageParam
     */
    Pagina(PageParam atributes);

    /*!
     * \brief Elimina Página
     */
    void deleteSelf();

    //----------------Get Atributes----------------//

    /*!
     * \brief Devolve ID da Página.
     * \return int - ID do Página.
     */
    int getID();
    /*!
     *\brief Devolve Descrição da Página
     *\return Descrição da Página
     */
    QString getDescription();

    /*!
     * \brief Devolve caminho da diretoria da Página
     * \return caminho da diretoria da Página
     */
    QDir getPath();

    /*!
     * \brief Devolve o tipo de Página
     * \return Tipo de Página
     */
    virtual pageType_t getType()=0;

    /*!
     * \brief Devolve a data de inicio do evento da Página
     * \return Data de Inicio
     */
    virtual QDate getStartDate()=0;

    /*!
     * \brief Devolve a data de fim do evento da Página
     * \return Data de Fim
     */
    virtual QDate getEndDate()=0;

    /*!
     * \brief Devolve o tipo de Festa
     * \return Tipo de Festa
     */
    virtual QString getPartyType()=0;

    /*!
     * \brief Devolve Fotos da Página
     * \return ponteiro para vetor de classes Foto
     */
    QVector<Foto *> *getPhotos();

    /*!
     * \brief Retorna album da Página
     * \return Ponteiro para classe Album
     */
    Album* parent();

    //-------------------Create--------------------//

    /*!
     * \brief Cria nova %Foto
     *
     * Cria nova %Foto com os atributos definidos em atributes
     * \param atributes - Estrutura PhotoParam
     * \return Ponteiro para a classe Foto
     */
    Foto* createPhoto(PhotoParam atributes);


    /* DELETE AND MOVE NOT YET IMPLEMENTED
     * int acceptPhoto(Foto* photo);
    int removePhoto(Foto* photo);
    int deletePhoto(Foto* photo);
    */
    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


protected:
    /*!
     * \brief createFolder
     * \param folderName
     * \return
     */
    int createFolder(QString folderName);

    /*!
     * \brief createFolderName
     * \return
     */
    virtual QString createFolderName()=0;

    QString Description;
    int ID;
    QDir Path;

    Album* Parent;
    GestorBD* oGestor;
    QVector<Foto*> *Photos;
};

/*!
 * \brief Subclasse da classe Pagina
 */
class PaginaViagem : public Pagina
{
public:

    PaginaViagem(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:

    QString createFolderName();

    QDate StartDate;
    QDate EndDate;

};

/*!
 * \brief Subclasse da classe Pagina
 */
class PaginaFesta : public Pagina
{
public:

    PaginaFesta(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

    QDate Date;
    QString PartyType;

};

/*!
 * \brief Subclasse da classe Pagina
 */
class PaginaCoisaPessoa : public Pagina
{
public:

    PaginaCoisaPessoa(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

};

/*!
 * \brief Subclasse da classe Pagina
 */
class PaginaOutro : public Pagina
{
public:

    PaginaOutro(PageParam atributes);

    pageType_t getType();

    QDate getStartDate();
    QDate getEndDate();
    QString getPartyType();

private:
    QString createFolderName();

    QDate StartDate;
    QDate EndDate;
};


#endif // PAGINA_H
