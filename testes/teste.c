#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Struct criado para o Registro de Cabeçalho 
typedef struct {
  char status;
  int *topo;
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
    - abertura do arquivo csv
    - abertura do arquivo estacao.bin
    - criação do registro de cabeçalho com dados iniciais e inserção no bin
    - leitura dos dados do arquivo csv
    - escrita dos dados no arquivo bin
*/
void criar_arquivo_bin(){
  // abertura do arquivo csv para leitura
  FILE *arq;
  arq = fopen("estacao.csv", "r+");

  if (arq == NULL){
    printf("Falha no processamento de arquivo.");
    return;
  }

  // abertura do arquivo bin para escrita
  FILE *arqBin;
  arqBin = fopen("estacao.bin", "wb");

  if (arqBin == NULL){
    printf("Falha no processamento de arquivo.");
    return;
  }

  // criação do Registro de Cabeçalho
  RegistroCabecalho registro_cabecalho;
  registro_cabecalho.status = '0';
  //registro_cabecalho.topo = -1;
  registro_cabecalho.proxRRN = 0;
  registro_cabecalho.nroEstacoes = 0;
  registro_cabecalho.nroParesEstacoes = 0;

  // inserção do registro de cabeçalho no bin
  fwrite(&registro_cabecalho, sizeof(RegistroCabecalho), 1, arqBin);

  fclose(arq);
  fclose(arqBin);
}


void ler_arquivo_bin(){
  FILE *arqBin;
  arqBin = fopen("estacao.bin", "rb");

  if (arqBin == NULL){
    printf("Falha no processamento do arquivo.");
    return;
  }

  RegistroCabecalho registro_cabecalho;
  if (fread(&registro_cabecalho, sizeof(RegistroCabecalho), 1, arqBin)){
    printf("Status: %c, ProxRRN: %d", registro_cabecalho.status, registro_cabecalho.proxRRN);
  } else {
    printf("Erro ao ler.");
  }

  fclose(arqBin);
  return;
}

int main(){
  ler_arquivo_bin();
  return 0;
}