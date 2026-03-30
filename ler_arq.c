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
    char *nomeEstacao_valor;
    int tamNomeEstacao_valor;
    if (strcmp(nomeEstacao, "") == 0){
      nomeEstacao_valor = NULL;
      tamNomeEstacao_valor = 0;
    } else {
      nomeEstacao_valor = strdup(nomeEstacao);
      tamNomeEstacao_valor = strlen(nomeEstacao);
    }

    char *codLinha = strsep_n(&bf_c, ",");
    int codLinha_valor = verificar_nulo_fixo(codLinha);
    
    char *nomeLinha = parse_str_token(&bf_c, ",");
    char *nomeLinha_valor;
    int tamNomeLinha_valor;
    if (strcmp(nomeLinha, "") == 0){
      nomeLinha_valor = NULL;
      tamNomeLinha_valor = 0;
    } else {
      nomeLinha_valor = nomeLinha;
      tamNomeLinha_valor = strlen(nomeLinha);
    }

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

