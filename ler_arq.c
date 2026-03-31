/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ler_arq.h"
#include "structs.h"

static char *strsep_n (char **stringp, const char *delim){
  char *begin, *end;
  begin = *stringp;
  if (begin == NULL) return NULL;
  end = begin + strcspn (begin, delim);
  if (*end) {
      *end++ = '\0';
      *stringp = end;
    }
  else *stringp = NULL;
  return begin;
}


/*!
  * @brief Lê uma token que é uma string e retorna esta string.
  *
  * @param[in,out] token_string Token string que contem a string que deve ser resgatada. Avança a string para o strsep.
  *
  * @param delim Delimitador para secionar a string.
  *
  * @return Retorna a string resgatada. Ela é alocada dinâmicamente.
 */
static char *parse_str_token(char** token_string, const char* delim) {
    char* str_contents = strsep_n(token_string, delim);
    unsigned long str_size = strlen(str_contents);
    char* str = calloc(str_size + 1, sizeof(char));
    if (str == NULL) exit(1);
    memcpy(str, str_contents, str_size);

    return str;
}


char check_eof (FILE* arq){
	char ch = 0;
	ch = fgetc(arq);
	fseek(arq, -1, SEEK_CUR);
	return (ch==EOF)?0:1;
}


int verificar_nulo_fixo(char *string){
  if (strcmp(string, "") == 0){
      return -1;
    } else {
      return atoi(string);
    }
}


RegistroDado ler_reg_dado_csv(FILE* arq) {
    char* bf = calloc(100, sizeof(char));
    if (!bf) exit(1);
    char* bf_c = bf;
    fgets(bf, 100, arq);
    bf[strcspn(bf, "\r\n")] = '\0';

    // valor codEstacao não pode ser nulo
    char *codEstacao = strsep_n(&bf_c, ",");
    int codEstacao_valor;
    if (codEstacao == NULL || codEstacao[0] == '\0') {
      printf("ERRO: valor nulo encontrado.\n");
      codEstacao_valor = -1;
    } else {
      codEstacao_valor = atoi(codEstacao);
    }
    
    // valor nomeEstacao não pode ser nulo
    char *nomeEstacao = parse_str_token(&bf_c, ",");
    char *nomeEstacao_valor = NULL;
    int tamNomeEstacao_valor = 0;
    if (strcmp(nomeEstacao, "") != 0){
      nomeEstacao_valor = strdup(nomeEstacao);
      tamNomeEstacao_valor = (int)strlen(nomeEstacao);
    }
    free(nomeEstacao);

    char *codLinha = strsep_n(&bf_c, ",");
    int codLinha_valor = verificar_nulo_fixo(codLinha);
    
    char *nomeLinha = parse_str_token(&bf_c, ",");
    char *nomeLinha_valor = NULL;
    int tamNomeLinha_valor = 0;
    if (strcmp(nomeLinha, "") != 0){
      nomeLinha_valor = strdup(nomeLinha);
      tamNomeLinha_valor = (int)strlen(nomeLinha);
    }
    free(nomeLinha);

    char *codProxEstacao = strsep_n(&bf_c, ",");
    int codProxEstacao_valor = verificar_nulo_fixo(codProxEstacao);

    char *distProxEstacao = strsep_n(&bf_c, ",");
    int distProxEstacao_valor = verificar_nulo_fixo(distProxEstacao);

    char *codLinhaIntegra = strsep_n(&bf_c, ",");
    int codLinhaIntegra_valor = verificar_nulo_fixo(codLinhaIntegra);

    char *codEstIntegra = strsep_n(&bf_c, ",");
    int codEstIntegra_valor = verificar_nulo_fixo(codEstIntegra);

    free(bf);
    return (RegistroDado){.removido = '0', .proximo = -1, .codEstacao = codEstacao_valor, .codLinha = codLinha_valor, .codProxEstacao = codProxEstacao_valor, .distProxEstacao = distProxEstacao_valor, .codLinhaIntegra = codLinhaIntegra_valor, .codEstIntegra = codEstIntegra_valor, .tamNomeEstacao = tamNomeEstacao_valor, .nomeEstacao = nomeEstacao_valor, .tamNomeLinha = tamNomeLinha_valor, .nomeLinha = nomeLinha_valor};
}


RegistroDado *ler_reg_dado_bin(FILE* arqBin){
  RegistroDado *r = (RegistroDado*) malloc(sizeof(RegistroDado));

  if (r == NULL) return NULL;

  // inicializando os ponteiros
  r->nomeEstacao = NULL;
  r->nomeLinha = NULL;

  int bytes_lidos = 0;

  fread(&r->removido, sizeof(char), 1, arqBin);
  fread(&r->proximo, sizeof(int), 1, arqBin);
  fread(&r->codEstacao, sizeof(int), 1, arqBin);
  fread(&r->codLinha, sizeof(int), 1, arqBin);
  fread(&r->codProxEstacao, sizeof(int), 1, arqBin);
  fread(&r->distProxEstacao, sizeof(int), 1, arqBin);
  fread(&r->codLinhaIntegra, sizeof(int), 1, arqBin);
  fread(&r->codEstIntegra, sizeof(int), 1, arqBin);

  fread(&r->tamNomeEstacao, sizeof(int), 1, arqBin);
  // não verificamos que o nomeEstacao é vazio
  if (r->tamNomeEstacao > 0){
    // como o nomeEstacao é um ponteiro na struct, é preciso alocar espaço primeiro antes de ler
    r->nomeEstacao = (char*) malloc((size_t)r->tamNomeEstacao + 1);
    fread(r->nomeEstacao, sizeof(char), (size_t)r->tamNomeEstacao, arqBin);
  } 

  fread(&r->tamNomeLinha, sizeof(int), 1, arqBin);
  if (r->tamNomeLinha > 0){
    // como o nomeLinha é um ponteiro na struct, é preciso alocar espaço primeiro antes de ler
    r->nomeLinha = (char*) malloc((size_t)r->tamNomeLinha + 1);
    fread(r->nomeLinha, sizeof(char), (size_t)r->tamNomeLinha, arqBin);
  } else {
    r->nomeLinha = NULL;
  }

  // quantidade de bytes dos valores fixos (int) + removido(char) + proximo (int) + bytes dos campos variáveis
  bytes_lidos = 37 + r->tamNomeEstacao + r->tamNomeLinha;

  // se o registro que lemos tem menos de 80 bytes, então pula para o próximo
  int lixo = 80 - bytes_lidos;
  if (lixo > 0){
    fseek(arqBin, lixo, SEEK_CUR);
  }

  // adicionando \0 nas strings para não imprimir lixo
  if (r->tamNomeEstacao > 0) r->nomeEstacao[r->tamNomeEstacao] = '\0';
  if (r->tamNomeLinha > 0) r->nomeLinha[r->tamNomeLinha] = '\0';

  return r;
}


RegistroCabecalho *ler_reg_cab_bin(FILE* arqBin){
  RegistroCabecalho *h = (RegistroCabecalho*) malloc(sizeof(RegistroCabecalho));

  if (h == NULL) return NULL;

  fread(&h->status, sizeof(char), 1, arqBin);
  fread(&h->topo, sizeof(int), 1, arqBin);
  fread(&h->proxRRN, sizeof(int), 1, arqBin);
  fread(&h->nroEstacoes, sizeof(int), 1, arqBin);
  fread(&h->nroParesEstacoes, sizeof(int), 1, arqBin);

  return h;
}


