#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include <string.h>
#include <stdio.h>

#include "structs.h"
#include "ler_arq.h"
#include "escrever_arq.h"

/*!
 * @brief Funcionalidade para criação do arquivo binário a partir de um csv, com registro de cabeçalho e registros de dados.
 *
 * @param nomeArq Nome do arquivo.
 *
 */
void funcionalidade1(const char *nomeArq, const char *nomeArqBin);

#endif