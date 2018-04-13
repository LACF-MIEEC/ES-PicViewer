#ifndef DESCRIPTION_H
#define DESCRIPTION_H

/*!
 *
 *
 * \mainpage Pic Viewer
 *
 * \subsection Documentção relativa à primeira versão do código fonte implementado.
 *
 * \section intro_sec Introdução
 *
 * Tal como planeado e mencionado nas etapas anteriores do presente projeto, para satisfazer as funcionalidades que são impostas no problema, <br>
 * recorremos a uma arquitetura de software orientada a objetos que faz a gestão das entidades Álbum, Página, %Foto e %Pessoa cujas classes <br>
 * implementadas são Album, Pagina, Foto e Pessoa, respetivamente.
 *
 * Toda a informação do software é armazenada numa base de dados que foi implementada com 5 tabelas, 4 delas representativas das entidades acima <br>
 * referidas e a restante para armazenar as associações entre Fotos e Pessoas. Esta última tabela aumenta a eficiencia da Base de dados uma vez <br>
 * que permite não ter informação repetida nas tabelas, evitando assim redundância nos dados.
 *
 * Esta Base de dados é apenas acessivél pela classe GestorBD, classe essa responsável pela troca de informação entre classes e a Base de dados, <br>
 * diminuindo este tipo de implementação a dependência do Software e consequentement tornando-o mais modular.
 *
 * Para que estas implementações façam sentido, foi também desenvolvida uma interface gráfica que permite ao utilizador, de uma maneira eficaz e <br>
 * intuitiva, gerir e consultar toda a informação por ele gerada.
 *
 * O problema fica assim decomposto em 3 partes principais, todas elas desacopladas suficientemente para que o seu desenvolvimento e manutenção <br>
 * seja simples e de baixo custo.
 *
 *
 *
 *
 * \section install_sec Requisitos não implementados
 *
 * O Software ainda não se encontra completamente implementado pelo que seguem os requisitos que apenas serão<br>
 * implementados na próxima etapa:
 *
 * - Associação entre Pessoas e Fotos
 * - Escolha
 * - Apresentação em slides
 * #- Reproduxir áudio
 * #- Configurar tempo entre Fotos
 * - (...)
 *
 *
 *
 *
 *
 *
 *\file album.h
 *\brief Contém a classe Album.
 *
 * Este ficheiro contém também uma estrutura com os parâmetros da classe (AlbumParam).
 *
 *
 *\file description.h
 *\brief Contém descrições adicionais necessárias ao Doxygen.
 *
 *
 *\file foto.h
 *\brief Contém a classe Foto.
 *
 * Este ficheiro contém também uma estrutura com os parâmetros da classe (PhotoParam).
 *
 *
 *\file gestorbd.h
 *\brief Contém a classe GestorBD.
 *
 *
 *\file listaalbuns.h
 *\brief Contém a classe ListaAlbuns.
 *
 *
 *\file listapessoas.h
 *\brief Contém a classe ListaPessoas.
 *
 *
 *\file pagina.h
 *\brief Contém a classe Pagina.
 *
 * Este ficheiro contém também uma estrutura com os parâmetros da classe (PageParam).
 *
 *
 *\file pessoa.h
 *\brief Contém a classe Pessoa.
 *
 * Este ficheiro contém também uma estrutura com os parâmetros da classe (PersonParam).
 */
#endif // DESCRIPTION_H
