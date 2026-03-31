/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H


/*!
 * @brief Funcionalidade 1 para criação do arquivo binário a partir de um csv, com registro de cabeçalho e registros de dados.
 *
 */
void criar_arq_bin();


/*!
 * @brief Funcionalidade 2 para mostrar todos os dados dos registros de dados do arquivo binário
 *
 */
void buscar_todos_reg_bin();


/*!
 * @brief Funcionalidade 3 para mostrar o registro buscado por dados especificados na entrada.
 *
 */
void buscar_reg_filtro();


/*!
 * @brief Funcionalidade 4 para mostrar o registro buscado pelo RRN
 *
 */
void buscar_reg_RRN();


/*!
 * @brief Busca os valores do registro de cabeçalho.
 *
 */
void buscar_reg_cab_bin();


/*!
 * @brief Serve para imprimir o conteúdo de um registro de dado.
 *
 * @param r O registro de dado.
 *
 */
void imprimir_reg_dado(RegistroDado *r);

/*!
 * @brief Função auxiliar para mostrar o registro de cabeçalho.
 *
 * @param h O registro de dado.
 *
 */
void imprimir_reg_cab(RegistroCabecalho *h);

#endif