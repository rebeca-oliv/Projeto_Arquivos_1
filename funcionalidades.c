#include <string.h>
#include <stdio.h>

#include "structs.h"
#include "ler_arq.h"
#include "escrever_arq.h"

void funcionalidade1(const char *nomeArq, const char *nomeArqBin){
  FILE *arqCsv = fopen(nomeArq, "r");
  if (arqCsv == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  FILE *arqBin = fopen(nomeArqBin, "wb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  RegistroCabecalho regCab;
  inicializar_cabecalho(&regCab);
  escreve_reg_cab_bin(arqBin, &regCab);

  // descarta a primeira linha com os nomes dos campos
  char bf_lixo[256];
  fgets(bf_lixo, sizeof(bf_lixo), arqCsv);

  int contRRN = 0, contEstacoes = 0, contPares = 0;

  // lista dos nomes das estações únicas
  char *estacoes[500];

  while (check_eof(arqCsv)){
    RegistroDado regDado = ler_reg_dado_csv(arqCsv);

    // quando é -1, quer dizer que não tem integração
    if (regDado.codEstIntegra != -1){
      contPares++;
    }

    // precisa verificar se os nomes são iguais 
    int jaTem = 0;
    for (int i = 0; i < contEstacoes; i++){
      if (strcmp(regDado.nomeEstacao, estacoes[i]) == 0)
        jaTem = 1;
        break;
    }

    if (!jaTem){
      // faz uma cópia para não ser apagado depois com o free
      estacoes[contEstacoes] = strdup(regDado.nomeEstacao);
      contEstacoes++;
    }

    escreve_reg_dado_bin(arqBin, &regDado);
    contRRN++;

    free_reg_dado(&regDado);
  }

  regCab.status = '1';
  regCab.nroEstacoes = contEstacoes;
  regCab.proxRRN = contRRN; 
  regCab.nroParesEstacoes = contPares;
  
  escreve_reg_cab_bin(arqBin, &regCab);

  // dando free na lista de nomes de estações únicas
  for (int i = 0; i < contEstacoes; i++){
    free(estacoes[i]);
  }

  fclose(arqCsv);
  fclose(arqBin);
}