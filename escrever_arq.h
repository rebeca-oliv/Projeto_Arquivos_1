#include <string.h>
#include <stdio.h>

#include "structs.h"

/*!
 * @brief Função auxiliar para checa se o valor recebido do arquivo csv é nulo.
 *
 * @param string Valor recebido do csv.
 *
 * @return Retorna um int com o valor -1 se nulo, ou com o valor especificado.
 */
int verificar_nulo_fixo(char *string);

/*!  
 * @brief Inicializar os valores iniciais do registro de cabeçalho.
 *
 * @param cab Struct que irá receber os valores iniciais.
 * 
 */
void inicializar_cabecalho(RegistroCabecalho *cab);

/*!  
 * @brief Escreve um header em um arquivo binario.
 *
 * @param f É o arquivo binário no qual deseja-se
 * escrever o header. O arquivo precisa estar em
 * um modo que permite a escrita.
 * O ponteiro de arquivo é movido.
 * 
 * @param h É o header que deseja escrever.
 */
void escreve_reg_cab_bin(FILE* f, const RegistroCabecalho* h);

/*!  
 * @brief Escreve um registro em um arquivo binario.
 *
 * @param f É o arquivo binário no qual deseja-se
 * escrever o registro. O arquivo precisa estar em
 * um modo que permite a escrita.
 * O ponteiro de arquivo é movido.
 * 
 * @param r É o registro que deseja escrever.
 */
void escreve_reg_dado_bin(FILE* f, const RegistroDado* r);