/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#ifndef LER_ARQ_H
#define LER_ARQ_H


#include "structs.h"

/*!
 * @brief Checa se é o fim do arquivo.
 *
 * @param arq Arquivo csv para checar. Ele precisa permitir leitura.
 *
 * @return Retorna 0 caso seja o fim do arquivo, 1 caso o contrario.
 */
char check_eof (FILE* arq);

/*!
 * @brief Função auxiliar para checa se o valor recebido do arquivo csv é nulo.
 *
 * @param string Valor recebido do csv.
 *
 * @return Retorna um int com o valor -1 se nulo, ou com o valor especificado.
 */
int verificar_nulo_fixo(char *string);

/*!
 * @brief Lê uma linha do arquivo csv e resgata os dados para um registro.
 *
 * @param f Arquivo csv para ser lido. Precisa estar aberto no modo leitura.
 *
 * @return Retorna um RegistroDado com os valores lidos da linha do csv.
 */
RegistroDado ler_reg_dado_csv(FILE* f);

/*!
 * @brief Lê registro de cabeçalho do arquivo bin e resgata os dados para um registro.
 *
 * @param arqBin Arquivo bin para ser lido. Precisa estar aberto no modo leitura.
 *
 * @return Retorna um RegistroCabecalho com os valores lidos do bin.
 */
RegistroCabecalho *ler_reg_cab_bin(FILE* arqBin);

/*!
 * @brief Lê registro do arquivo bin e resgata os dados para um registro.
 *
 * @param arqBin Arquivo bin para ser lido. Precisa estar aberto no modo leitura.
 *
 * @return Retorna um RegistroDado com os valores lidos da linha do bin.
 */
RegistroDado *ler_reg_dado_bin(FILE* arqBin);

#endif