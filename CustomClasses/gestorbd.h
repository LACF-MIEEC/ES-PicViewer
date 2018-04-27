#ifndef GESTORBD_H
#define GESTORBD_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QDate>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


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


extern QDir DBPath;
////////////////////////////////////////////////
/*!
 * \brief Classe responsável por gerir todos os acessos de escrita e leitura na base de dados.
 *
 * Abstrai as restantes classes do acesso à Base de Dados sendo a única com acesso à mesma.
 */
class GestorBD
{
public:


    ////////////////////////////////////////////////
    /*!
     * \brief Construtor.
     *
     * Inicia coneção com a Base de Dados.
     * \param path - Caminho Absoluto para o ficheiro da Base de Dados.
     */
    GestorBD(const QString& path);


    ////////////////////////////////////////////////
    /*!
     * \brief Destrutor.
     *
     * Fecha a coneção com a Base de Dados.
     * \param path - Caminho Absoluto para o ficheiro da Base de Dados.
     */
    ~GestorBD();


    //-------------------Create--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Cria as tabelas da Base de Dados.
     * \return True - Tabelas criadas, False - Tabelas não criadas.
     */
    bool createTables();


    //-------------------add--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona nova %Foto à Base de Dados.
     * \param newPhoto - Ponteiro para a classe Foto.
     * \return True - %Foto Adicionada, False - %Foto não adicionada.
     */
    bool addPhoto(Foto*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona novo Álbum à Base de Dados.
     * \param newAlbum - Ponteiro para a classe Album.
     * \return True - Álbum Adicionado, False - Álbum não adicionado.
     */
    bool addAlbum(Album*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona nova Página à Base de Dados.
     * \param newPage - Ponteiro para a classe Pagina.
     * \return True - Página Adicionada, False - Página não adicionada.
     */
    bool addPage(Pagina*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona nova %Pessoa à Base de Dados.
     * \param newPerson - Ponteiro para classe Pessoa.
     * \return True - %Pessoa Adicionada, False - %Pessoa não adicionada.
     */
    bool addPerson(Pessoa*);
    //-------------------------------------------------------------
    //UPDATE
    //-------------------------------------------------------------


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da %Foto pretendida.
     *
     * A %Foto pretendida obtém-se através do seu ID definido em newPhoto.
     * \param newPhoto - Ponteiro para a classe Foto.
     * \return True - %Foto Atualizada, False - %Foto não Atualizada.
     */
    bool updatePhoto(PhotoParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações do Álbum pretendido.
     *
     * O Álbum pretendido obtém-se através do seu ID definido em newAlbum.
     * \param newAlbum - Ponteiro para a classe Album.
     * \return True - Álbum Atualizado, False - Álbum não Atualizado.
     */
    bool updateAlbum(Album*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da Página pretendido.
     *
     * A Página pretendida obtém-se através do seu ID definido em newPage.
     * \param newPage - Ponteiro para a classe Pagina.
     * \return True - Página Atualizada, False - Página não Atualizada.
     */
    bool updatePage(Pagina*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da %Pessoa pretendida.
     *
     * A %Pessoa pretendida obtém-se através do seu ID definido em newPerson.
     * \param newPerson - Ponteiro para a classe Pessoa.
     * \return True - %Pessoa Atualizada, False - %Pessoa não Atualizada.
     */
    bool updatePerson(Pessoa *);


    //-------------------get--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Fotos da Página pretendida.
     *
     * A pesquisa é feita através do ID da página definido em Page.
     * \param Page - Ponteiro para a classe Pagina .
     * \return Vetor de Estruturas PhotoParam com atributos das Fotos.
     */
    QVector<PhotoParam *> *getPhotos(Pagina *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Páginas do Álbum pretendido.
     *
     * A pesquisa é feita através do ID do Álbum definido em Alb.
     * \param Alb - Ponteiro para a classe Album.
     * \return Vetor de Estruturas PageParam com atributos das Páginas.
     */
    QVector<PageParam *> *getPages(Album *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todos os Álbuns existentes.
     *
     * \param Albs - ponteiro para a classe ListaAlbuns.
     * \return Vetor de Estruturas AlbumParam com atributos dos Álbuns.
     */
    QVector<AlbumParam *> *getAlbums(ListaAlbuns *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Pessoas existentes.
     *
     * \param People - Ponteiro para a classe ListaPessoas.
     * \return Vetor de Estruturas PersonParam com atributos das Pessoas.
     */
    QVector<PersonParam *> *getPeople(ListaPessoas *);


    //-------------------delete--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Elimina %Foto pretendida.
     *
     * A %Foto pretendida obtém-se através do seu ID definido em delPhoto.
     * \param delPhoto - Ponteiro para a classe Foto.
     * \return True - %Foto Eliminada, False - %Foto não Eliminada.
     */
    bool deletePhoto(Foto*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina Álbum pretendido.
     *
     * O Álbum pretendido obtém-se através do seu ID definido em delAlbum.
     * \param delAlbum - Ponteiro para a classe Album.
     * \return True - Álbum Atualizado, False - Álbum não Atualizado.
     */
    bool deleteAlbum(Album*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina Página pretendida.
     *
     * A Página pretendida obtém-se através do seu ID definido em delPage.
     * \param delPage - Ponteiro para a classe Pagina.
     * \return True - Página Eliminada, False - Página não Eliminada.
     */
    bool deletePage(Pagina*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina %Pessoa pretendida.
     *
     * A %Pessoa pretendida obtém-se através do seu ID definido em delPerson.
     * \param delPerson - Ponteiro para a classe Pessoa.
     * \return True - %Pessoa Eliminada, False - %Pessoa não Eliminada.
     */
    bool deletePerson(Pessoa*);


    //-------------------Create--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Remove as Tabelas Criadas.
     * \return True - Tabelas Eliminadas, False - Tabelas não Eliminadas.
     */
    bool removeAll();


    ////////////////////////////////////////////////
    /*!
     * \brief Reinicia todas as Tabelas Criadas.
     * \return True - Tabelas Reiniciadas, False - Tabelas não Reiniciadas.
     */
    bool clearAll();


    ////////////////////////////////////////////////
    /*!
     * \brief isOpen
     * \return
     */
    bool isOpen() const;


    ////////////////////////////////////////////////
    //bool updateAtachment(const QString& , const QString&, const QString &);


    ////////////////////////////////////////////////
    //bool addAtachment(const QString& ,const QString&);


    ////////////////////////////////////////////////
    //bool getPeopleByFoto(const QString&);


    ////////////////////////////////////////////////
    //bool getAtachments();

private:
    QSqlDatabase m_db;
};

#endif // GESTORBD_H
