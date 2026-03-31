#include <string.h>
#include <stdio.h>

#include "structs.h"
#include "ler_arq.h"
#include "escrever_arq.h"

// Funcionalidade 1
void criar_arq_bin(const char *nomeArq, const char *nomeArqBin){
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

  RegistroCabecalho h;
  inicializar_cabecalho(&h);
  escreve_reg_cab_bin(arqBin, &h);

  // descarta a primeira linha com os nomes dos campos
  char bf_lixo[256];
  fgets(bf_lixo, sizeof(bf_lixo), arqCsv);

  int contRRN = 0, contEstacoes = 0, contPares = 0;

  // lista dos nomes das estações únicas
  char *estacoes[500];

  while (check_eof(arqCsv)){
    RegistroDado r = ler_reg_dado_csv(arqCsv);

    // quando é -1, quer dizer que não tem integração
    if (r.codEstIntegra != -1){
      contPares++;
    }

    // precisa verificar se os nomes são iguais 
    int jaTem = 0;
    for (int i = 0; i < contEstacoes; i++){
      if (strcmp(r.nomeEstacao, estacoes[i]) == 0){
        jaTem = 1;
        break;
      }
    }

    if (!jaTem){
      // faz uma cópia para não ser apagado depois com o free
      estacoes[contEstacoes] = strdup(r.nomeEstacao);
      contEstacoes++;
    }

    escreve_reg_dado_bin(arqBin, &r);
    contRRN++;

    free_reg_dado(&r);
  }

  h.nroEstacoes = contEstacoes;
  h.proxRRN = contRRN; 
  h.nroParesEstacoes = contPares;
  
  escreve_reg_cab_bin(arqBin, &h);

  // dando free na lista de nomes de estações únicas
  for (int i = 0; i < contEstacoes; i++)
    free(estacoes[i]);

  fclose(arqCsv);
  fclose(arqBin);
}


void imprimir_reg_dado(RegistroDado *r){
  // esses dados nunca podem ser nulos, por isso, não serão tratados
  printf("%d ", r->codEstacao);
  printf("%s ", r->nomeEstacao);

  if (r->codLinha == -1) printf("NULO ");
  else printf("%d ", r->codLinha);

  if (r->nomeLinha == "") printf("NULO ");
  else printf("%s ", r->nomeLinha);

  if (r->codProxEstacao == -1) printf("NULO ");
  else printf("%d ", r->codProxEstacao);

  if (r->distProxEstacao == -1) printf("NULO ");
  else printf("%d ", r->distProxEstacao);

  if (r->codLinhaIntegra == -1) printf("NULO ");
  else printf("%d ", r->codLinhaIntegra);

  if (r->codEstIntegra == -1) printf("NULO\n");
  else printf("%d\n", r->codEstIntegra);
}


void imprimir_reg_cab(RegistroCabecalho *h){
  printf("%c %d %d %d %d\n", h->status, h->topo, h->proxRRN, h->nroEstacoes, h->nroParesEstacoes);
}

void mostrar_reg_cab_bin(const char *nomeArqBin){
  // abrir arquivo binário para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  fseek(arqBin, 0, SEEK_SET);

  RegistroCabecalho *h = ler_reg_cab_bin(arqBin);
  imprimir_reg_cab(h);

  free_reg_cab(h);
  fclose(nomeArqBin);
}

// Funcionalidade 2
void mostrar_todos_reg_bin(const char *nomeArqBin){
  // abrir arquivo binário para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // pular para o byte dos registros de dados
  fseek(arqBin, 17, SEEK_SET);

  while (check_eof(arqBin)){
    RegistroDado *r = ler_reg_dado_bin(arqBin);
    imprimir_reg_dado(r);
    
    free_reg_dado(r);
  }

  fclose(arqBin);
}