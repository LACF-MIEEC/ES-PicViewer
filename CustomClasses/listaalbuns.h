#ifndef LISTAALBUNS_H
#define LISTAALBUNS_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include "album.h"
/*!
 * \brief Classe responsável por fazer a gestão de Álbums.
 *
 * Responsável pela construção e desconstrução de objectos no iniciar do Programa
 */
class ListaAlbuns
{
public:
    ////////////////////////////////////////////////
    /*!
     * \brief Construtor
     * \param gestor - Ponteiro para a classe GestorBD
     */
    ListaAlbuns(GestorBD* gestor=0);

    ////////////////////////////////////////////////
    /*!
      *\brief Destrutor
      */
    ~ListaAlbuns();

    ////////////////////////////////////////////////
    /*!
     * \brief Carrega Álbuns existentes na Base de Dados.
     *
     *  Reinicializa o Vector de Albuns existente, salvaguardar ponteiros(ou destruir objectos) antes de chamar;
     *
     * \param gestor - Ponteiro para a classe GestorBD.
     * \return True - Álbuns lidos, False - Álbuns não lidos.
     */
    bool loadAlbuns(QVector<int> &allocatedID, int &maxID, GestorBD* gestor=0);

    /*!
     * \brief Carrega todos os objectos (Album, Pagina e Foto) da BD
     *
     * Reinicializa o Vector de Albuns existente, salvaguardar ponteiros(ou destruir objectos) antes de chamar;
     * \param gestor - Ponteiro para a classe GestorBD.
     * \return True - Todos os objetos carregados, False - Falha ao carregar todos os objectos da BD.
     */
    bool loadAll(GestorBD* gestor=0);

    //----------------Get Atributes----------------//

    ////////////////////////////////////////////////
    /*!
     * \brief Devolve todos os Álbuns
     * \return Ponteiro para vetor de calsses Album
     */
    QVector<Album *> *getAlbums();

    //-------------------Create--------------------//

    ////////////////////////////////////////////////
    /*!
     * \brief Cria novo Álbum
     *
     * Cria um novo album com os atributos definidos em atributes
     * \param atributes - Estrutura AlbumParam
     * \return Ponteiro para a classe Album
     */
    Album* createAlbum(AlbumParam atributes);

    ////////////////////////////////////////////////
    /*!
     * \brief Cria nova Página
     *
     * Cria uma nova Página com os atributos definidos em atributes,
     * na página definida em destPage
     * \param atributes - Estrutura PageParam
     * \param destination - Ponteiro para a classe Album
     * \return Ponteiro para a classe Página
     */
    Pagina* createPage(PageParam atributes, Album* destination=0);

    ////////////////////////////////////////////////
    /*!
     * \brief Cria nova %Foto.
     * \param atributes - Estrutura PhotoParam.
     * \param destPage - Ponteiro para a classe Pagina
     * \param destAlbum - Ponteiro para a classe Album
     * \return Ponteiro para a classe Foto
     */
    Foto* createPhoto(PhotoParam atributes,Pagina* destPage, Album* destAlbum);

    /* REMOVE AND EDIT NOT YET IMPLEMENTED
    int deleteAlbum(Album* album);
    int editAlbum(Album* album, QString newName, QString newDesc);
    */
    /* MOVE AND SEARCH NOT YET IMPLEMENTED
    int movePage(Album* origin, Album* destination, Pagina* page);

    int movePhoto(Album* originAlbum, Pagina* originPage,
                  Album* destinationAlbum, Pagina* destinationPage,
                  Foto* photo);
    QVector<Foto*> searchPhotoByDate(QDate);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */

private:

    QVector<int> allocatedAlbumID;
    int maxAlbumID;

    QVector<int> allocatedPageID;
    int maxPageID;

    QVector<int> allocatedPhotoID;
    int maxPhotoID;

    int generateID(QVector<int> &allocatedID, int &maxID);
    int genAlbumID();
    int genPageID();
    int genPhotoID();

    QVector<Album*> *Albums;
    GestorBD* oGestor;
};

#endif // LISTAALBUNS_H
