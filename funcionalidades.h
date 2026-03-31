#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include <string.h>
#include <stdio.h>

#include "structs.h"
#include "ler_arq.h"
#include "escrever_arq.h"

/*!
 * @brief Funcionalidade 1 para criação do arquivo binário a partir de um csv, com registro de cabeçalho e registros de dados.
 *
 * @param nomeArq Nome do arquivo.
 * @param nomeArqBin Nome do arquivo binário.
 */
void criar_arq_bin(const char *nomeArq, const char *nomeArqBin);

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

/*!
 * @brief Funcionalidade 2 para mostrar todos os dados dos registros de dados do arquivo binário
 *
 * @param nomeArqBin Nome do arquivo binário.
 *
 */
void mostrar_todos_reg_bin(const char *nomeArqBin);
#endif