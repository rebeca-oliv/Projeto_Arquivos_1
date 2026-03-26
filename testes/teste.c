#include <stdio.h>
#include <stdlib.h>

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
    print("Falha no processamento de arquivo.");
    return 0;
  }

  // abertura do arquivo bin para escrita
  FILE *arqBin;
  arqBin = fopen("estacao.bin", "wb");

  if (arqBin == NULL){
    printf("Falha no processamento de arquivo.");
    return 0;
  }

  // criação do Registro de Cabeçalho
  RegistroCabecalho registro_cabecalho;
  registro_cabecalho.status = '0';
  //registro_cabecalho.topo = -1;
  registro_cabecalho.proxRRN = 0;
  registro_cabecalho.nroEstacoes = 0;
  registro_cabecalho.nroParesEstacoes = 0;

  // inserção do registro de cabeçalho no bin
  


  fclose(arq);
  fclose(arqBin);
}