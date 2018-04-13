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

#include "paramstructs.h"
#include "flags.h"

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
     * \param newPhoto - Estrutura PhotoParam.
     * \return True - %Foto Adicionada, False - %Foto não adicionada.
     */
    bool addPhoto(PhotoParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona novo Álbum à Base de Dados.
     * \param newAlbum - Estrutura AlbumParam.
     * \return True - Álbum Adicionado, False - Álbum não adicionado.
     */
    bool addAlbum(AlbumParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona nova Página à Base de Dados.
     * \param newPage - Estrutura PageParam.
     * \return True - Página Adicionada, False - Página não adicionada.
     */
    bool addPage(PageParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Adiciona nova %Pessoa à Base de Dados.
     * \param newPerson - Estrutura PersonParam.
     * \return True - %Pessoa Adicionada, False - %Pessoa não adicionada.
     */
    bool addPerson(PersonParam*);
    //-------------------------------------------------------------
    //UPDATE
    //-------------------------------------------------------------


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da %Foto pretendida.
     *
     * A %Foto pretendida obtém-se através do seu ID definido em newPhoto.
     * \param newPhoto - Estrutura PhotoParam.
     * \return True - %Foto Atualizada, False - %Foto não Atualizada.
     */
    bool updatePhoto(PhotoParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações do Álbum pretendido.
     *
     * O Álbum pretendido obtém-se através do seu ID definido em newAlbum.
     * \param newAlbum - Estrutura AlbumParam.
     * \return True - Álbum Atualizado, False - Álbum não Atualizado.
     */
    bool updateAlbum(AlbumParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da Página pretendido.
     *
     * A Página pretendida obtém-se através do seu ID definido em newPage.
     * \param newPage - Estrutura PageParam.
     * \return True - Página Atualizada, False - Página não Atualizada.
     */
    bool updatePage(PageParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Atualiza Informações da %Pessoa pretendida.
     *
     * A %Pessoa pretendida obtém-se através do seu ID definido em newPerson.
     * \param newPerson - Estrutura PersonParam.
     * \return True - %Pessoa Atualizada, False - %Pessoa não Atualizada.
     */
    bool updatePerson(PersonParam*);


    //-------------------get--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Fotos da Página pretendida.
     *
     * A pesquisa é feita através do ID da página definido em Page.
     * \param Page - Estrutura PageParam.
     * \return Vetor de Estruturas PhotoParam com atributos das Fotos.
     */
    QVector<PhotoParam *> *getPhotos(PageParam *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Páginas do Álbum pretendido.
     *
     * A pesquisa é feita através do ID do Álbum definido em Alb.
     * \param Alb - Estrutura AlbumParam.
     * \return Vetor de Estruturas PageParam com atributos das Páginas.
     */
    QVector<PageParam *> *getPages(AlbumParam *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todos os Álbuns existentes.
     *
     * \param Albs - Classe ListaAlbuns.
     * \return Vetor de Estruturas AlbumParam com atributos dos Álbuns.
     */
    QVector<AlbumParam *> *getAlbums(ListaAlbuns *);


    ////////////////////////////////////////////////
    /*!
     * \brief Procura na Base de Dados todas as Pessoas existentes.
     *
     * \param People - Classe ListaPessoas.
     * \return Vetor de Estruturas PersonParam com atributos das Pessoas.
     */
    QVector<PersonParam *> *getPeople(ListaPessoas *);


    //-------------------delete--------------------//
    ////////////////////////////////////////////////
    /*!
     * \brief Elimina %Foto pretendida.
     *
     * A %Foto pretendida obtém-se através do seu ID definido em delPhoto.
     * \param delPhoto - Estrutura PhotoParam.
     * \return True - %Foto Eliminada, False - %Foto não Eliminada.
     */
    bool deletePhoto(PhotoParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina Álbum pretendido.
     *
     * O Álbum pretendido obtém-se através do seu ID definido em delAlbum.
     * \param delAlbum - Estrutura AlbumParam.
     * \return True - Álbum Atualizado, False - Álbum não Atualizado.
     */
    bool deleteAlbum(AlbumParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina Página pretendida.
     *
     * A Página pretendida obtém-se através do seu ID definido em delPage.
     * \param delPage - Estrutura PageParam.
     * \return True - Página Eliminada, False - Página não Eliminada.
     */
    bool deletePage(PageParam*);


    ////////////////////////////////////////////////
    /*!
     * \brief Elimina %Pessoa pretendida.
     *
     * A %Pessoa pretendida obtém-se através do seu ID definido em delPerson.
     * \param delPerson - Estrutura PersonParam.
     * \return True - %Pessoa Eliminada, False - %Pessoa não Eliminada.
     */
    bool deletePerson(PersonParam*);


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
