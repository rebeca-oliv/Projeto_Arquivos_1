#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "pilha.h"

// Struct criado para o Registro de Cabeçalho 
typedef struct {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} RegistroCabecalho;

// Struct criado para o Registro de Dados 
typedef struct {
  char removido;
  int proximo;
  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int tamNomeEstacao;
  char *nomeEstacao;
  int tamNomeLinha;
  char *nomeLinha;
} RegistroDado;

/*
  Função para a criação do arquvo estacao.bin
    - abertura dos arquivos csv e bin
    - criação do registro de cabeçalho com dados iniciais e inserção no bin
    - leitura dos dados do arquivo csv
    - escrita dos dados no arquivo bin
*/
void criar_arquivo_bin(char *nomeArq, char *nomeArqBin){
  // abertura do arquivo csv para leitura
  FILE *arq;
  arq = fopen(nomeArq, "r+");

  if (arq == NULL){
    printf("Falha no processamento de arquivo.");
    return;
  }

  // abertura do arquivo bin para escrita
  FILE *arqBin;
  arqBin = fopen(nomeArqBin, "wb");

  if (arqBin == NULL){
    printf("Falha no processamento de arquivo.");
    return;
  }

  // criação do Registro de Cabeçalho inicial
  RegistroCabecalho regCab;

  regCab.status = '0';
  regCab.topo = -1;
  regCab.proxRRN = 0;
  regCab.nroEstacoes = 0;
  regCab.nroParesEstacoes = 0;

  // inserção do registro de cabeçalho no arquivo bin
  // registro de cabeçalho com 17 bytes
  fwrite(&regCab.status, sizeof(char), 1, arqBin);
  fwrite(&regCab.topo, sizeof(int), 1, arqBin);
  fwrite(&regCab.proxRRN, sizeof(int), 1, arqBin);
  fwrite(&regCab.nroEstacoes, sizeof(int), 1, arqBin);
  fwrite(&regCab.nroParesEstacoes, sizeof(int), 1, arqBin);

  // TEM QUE FAZER: fazer a inserção dos dados no arquivo bin
  // usa o fgets para ler do csv
  // usar um buffer - alocar dinamicamente (dar free)
  char linha[1024];


  fclose(arq);
  fclose(arqBin);
}

// É PARA REMOVER ESSA FUNÇÃO NO FINAL
void ler_arquivo_bin(char *nomeArqBin) {
    FILE *arqBin = fopen(nomeArqBin, "rb");
    if (arqBin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    RegistroCabecalho regCab;

    // Leitura campo a campo para garantir os 17 bytes exatos
    fread(&regCab.status, sizeof(char), 1, arqBin);
    fread(&regCab.topo, sizeof(int), 1, arqBin);
    fread(&regCab.proxRRN, sizeof(int), 1, arqBin);
    fread(&regCab.nroEstacoes, sizeof(int), 1, arqBin);
    fread(&regCab.nroParesEstacoes, sizeof(int), 1, arqBin);

    printf("--- Conteudo do Cabecalho ---\n");
    printf("Status: %c\n", regCab.status);
    printf("Topo: %d\n", regCab.topo);
    printf("ProxRRN: %d\n", regCab.proxRRN);
    printf("Nro Estacoes: %d\n", regCab.nroEstacoes);
    printf("Nro Pares: %d\n", regCab.nroParesEstacoes);

    fclose(arqBin);
}

int main(){

  // declaração e atribuição dos nomes dos arquivos
  char nomeArq[100];
  char nomeArqBin[100];
  scanf("%s %s", nomeArq, nomeArqBin);

  criar_arquivo_bin(nomeArq, nomeArqBin);
  ler_arquivo_bin(nomeArqBin);

  return 0;
}