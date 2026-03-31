/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} RegistroCabecalho;

typedef struct {
  char removido;
  int proximo;
  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;
  char *nomeEstacao;
  int tamNomeLinha;
  char *nomeLinha;
} RegistroDado;

/*! 
 * @brief Desaloca os campos dinâmicamente alocados do registro de cabeçalho.
 * 
 * @param h Registro de cabeçalho que precisa ser liberado.
 */
void free_reg_cab(RegistroCabecalho* h);

/*! 
 * @brief Desaloca os campos dinâmicamente alocados do registro de dado.
 * 
 * @param r Registro de dado que precisa ser liberado.
 */
void free_reg_dado(RegistroDado* r);

#endif