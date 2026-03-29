#include <string.h>
#include <stdio.h>

#include "structs.h"

/*!
 * @brief Checa se é o fim do arquivo.
 *
 * @param f Arquivo csv para checar. Ele precisa permitir leitura.
 *
 * @return Retorna 0 caso seja o fim do arquivo, 1 caso o contrario.
 */
char check_eof (FILE* f);

/*!
 * @brief Lê uma linha do arquivo csv e resgata os dados para um registro.
 *
 * @param f Arquivo csv para ser lido. Precisa estar aberto no modo leitura.
 *
 * @return Retorna um RegistroDado com os valores lidos da linha do csv.
 */
RegistroDado ler_reg_dado_csv(FILE* f);

