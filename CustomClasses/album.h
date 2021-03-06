    #ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

class Album;
class Pagina;
class Pessoa;
class Foto;

class GestorBD;
class ListaAlbuns;
class ListaPessoas;

struct PhotoParam;
struct PageParam;
struct AlbumParam;
struct PersonParam;

enum pageType_t:short int;
enum gender: short int;
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


/*!
 * \brief Classe representativa de um Álbum na ótica do utilizador.
 *
 * Contém as Páginas e as características associadas à representação de um Álbum.
 */
class Album
{
public:


    ////////////////////////////////////////////////
    /*!
     * \brief Construtor.
     * \param atributes - Estrutura AlbumParam.
     */
    Album(AlbumParam atributes);


    ////////////////////////////////////////////////
    /*!
     * \brief Destrutor.
     */
    ~Album();

    ////////////////////////////////////////////////
    /*!
     * \brief Carrega Páginas existentes na Base de Dados.
     *
     * Reinicializa o Vector de Paginas existente, salvaguardar ponteiros(ou destruir objectos) antes de chamar.
     * \param gestor - Ponteiro para a classe GestorBD.
     * \param allocatedID - Vetor de inteiros que representam os ID's já alocados.
     * \param maxID - Representa o número do maior ID criado.
     * \return True - Página(s) lidas, False - Página(s) não lidas.
     */
    bool loadPages(QVector<int> &allocatedID, int &maxID, GestorBD *gestor=0);


    ////////////////////////////////////////////////
    /*!
     * \brief Cria Pasta relativa ao Álbum.
     *
     * Cria Pasta com nome gerado pela função createFolderName.
     * \return True - Pasta criada, False - Pasta não criada.
     */

    bool createFolder();


    //----------------Get Atributes----------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Devolve ID do Álbum.
     * \return int - ID do Álbum.
     */
    int getID();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve nome do Álbum.
     * \return QString - Nome do Álbum.
     */
    QString getName();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Descrição do Álbum.
     * \return Descrição do Álbum.
     */
    QString getDescription();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve caminho da diretoria do Álbum.
     * \return Caminho da diretoria do Álbum.
     */
    QDir getPath();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve o tipo de página do Álbum.
     * \return Tipo de Página do Álbum.
     */
    pageType_t getPageType();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Páginas no Álbum.
     * \return Ponteiro para vetor de classes Pagina.
     */
    QVector<Pagina *> *getPages();


    ////////////////////////////////////////////////
    /*!
     * \brief Devolve Lista de Álbuns.
     * \return Ponteiro para a classe ListaAlbuns.
     */
    ListaAlbuns* parent();


    //-------------------Create--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Cria uma nova Página.
     *
     * Cria uma nova Página com os atributos recebidos em atributes.
     * \param atributes - estrutura PageParam.
     * \return Ponteiro para a classe Pagina.
     */
    Pagina* createPage(PageParam atributes);


    ////////////////////////////////////////////////
    /*!
     * \brief Cria uma nova Página.
     *
     * Cria uma nova %Foto na Página destination com os atributos atributes.
     * \param atributes - Estrutura PhotoParam.
     * \param destination - Ponteiro para a classe Pagina.
     * \return Ponteiro para a classe Foto.
     */
    Foto* createPhoto(PhotoParam atributes, Pagina* destination);


    /* MODIFICATIONS NOT YET IMPLEMENTED
    int setName(QString newName);
    void setDescription(QString newDesc);
    */

    /* DELETE AND MOVE NOT YET IMPLEMENTED
    int acceptPage(Pagina* page);
    int removePage(Pagina* page);
    int deletePage(Pagina* page);
    */

    //int acceptPhoto(Pagina* page, Foto* photo); //Mais vale ir logo à página se já tenho o ponteiro

    /* SEARCH NOT YET IMPLEMENTED
    QVector<Foto*> searchPhotoByDate(QDate date);
    QVector<Foto*> searchPhotoByKeyword(QString keyword);
    */


private:


    ////////////////////////////////////////////////
    /*!
     * \brief Gera nome para a diretoria representativa do Álbum.
     *
     * O nome do álbum é gerado retirando todos os carateres especiais e acentos.
     * do nome do Álbum e juntando o ID do album, separados por um "_".
     * \return Nome do Álbum.
     */

    QString createFolderName();

    int ID;
    QString Name;
    QString Description;
    QDir Path;
    pageType_t PageType;

    ListaAlbuns* Parent;
    GestorBD* oGestor;
    QVector<Pagina*> *Pages;

};

#endif // ALBUM_H
