/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "structs.h"
#include "ler_arq.h"
#include "escrever_arq.h"

// Função disponibilizada pelo monitor
void BinarioNaTela(char *arquivo) {
    FILE *fs;
    if (arquivo == NULL || !(fs = fopen(arquivo, "rb"))) {
        fprintf(stderr,
                "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): "
                "não foi possível abrir o arquivo que me passou para leitura. "
                "Ele existe e você tá passando o nome certo? Você lembrou de "
                "fechar ele com fclose depois de usar?\n");
        return;
    }

    fseek(fs, 0, SEEK_END);
    size_t fl = ftell(fs);

    fseek(fs, 0, SEEK_SET);
    unsigned char *mb = (unsigned char *)malloc(fl);
    fread(mb, 1, fl, fs);

    unsigned long cs = 0;
    for (unsigned long i = 0; i < fl; i++) {
        cs += (unsigned long)mb[i];
    }

    printf("%lf\n", (cs / (double)100));

    free(mb);
    fclose(fs);
}


// Funcionalidade 1
void criar_arq_bin(){
  char nomeArq[100];
  char nomeArqBin[100];

  scanf("%s %s", nomeArq, nomeArqBin);

  // abrir arquivo csv para leitura
  FILE *arqCsv = fopen(nomeArq, "r");
  if (arqCsv == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // abrir arquivo bin para escrita
  FILE *arqBin = fopen(nomeArqBin, "wb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  RegistroCabecalho *h = NULL;
  h = (RegistroCabecalho *) malloc(sizeof(RegistroCabecalho));
  if (h == NULL){
    fclose(arqCsv);
    fclose(arqBin);
    return;
  }

  inicializar_cabecalho(h);
  escreve_reg_cab_bin(arqBin, h);

  // descarta a primeira linha com os nomes dos campos
  char bf_lixo[256];
  fgets(bf_lixo, sizeof(bf_lixo), arqCsv);

  // variáveis auxiliares para definir os valores finais do reg cab no final dos reg de dados
  // 1. ações relacionadas ao contEstacoes
  // 2. ações relacionadas ao contPares
  int contRRN = 0, contEstacoes = 0, contPares = 0;

  // 1. lista dos nomes das estações únicas
  char *estacoes[1000];

  // 2. lista de vetores com os pares codEstacao e codProxEstacao
  int paresUnicos[1000][2];

  while (check_eof(arqCsv)){
    RegistroDado r = ler_reg_dado_csv(arqCsv);

    // 1. precisa verificar se os nomes são iguais 
    int jaTemNome = 0;
    for (int i = 0; i < contEstacoes; i++){
      if (strcmp(r.nomeEstacao, estacoes[i]) == 0){
        jaTemNome = 1;
        break;
      }
    }

    if (!jaTemNome){
      // 1. faz uma cópia para não ser apagado depois com o free
      estacoes[contEstacoes] = strdup(r.nomeEstacao);
      contEstacoes++; // 1. soma toda vez que tem um nome único
    }

    // 2. precisa verificar se o par [codEstacao, codProxEstacao] já existe
    int jaTemPar = 0;
    if (r.codProxEstacao != -1){
      for (int i = 0; i < contPares; i++){
        // 2. verifica se já existe o par no vetor
        if (paresUnicos[i][0] == r.codEstacao && paresUnicos[i][1] == r.codProxEstacao){
          jaTemPar = 1;
          break;
        }
      }

      if (!jaTemPar){
        // 2. salvando o novo par
        paresUnicos[contPares][0] = r.codEstacao;
        paresUnicos[contPares][1] = r.codProxEstacao;
        contPares++;
      }
    }

    escreve_reg_dado_bin(arqBin, &r);
    // soma toda vez que tem um registro novo
    contRRN++;

    free_reg_dado(&r);
  }

  // deve ser 1 depois de usar o arquivo para escrita
  //h->status = '1';
  h->nroEstacoes = contEstacoes;
  h->proxRRN = contRRN; 
  h->nroParesEstacoes = contPares;
  
  escreve_reg_cab_bin(arqBin, h);

  // dando free na lista de nomes de estações únicas
  for (int i = 0; i < contEstacoes; i++)
    free(estacoes[i]);

  fclose(arqCsv);
  fclose(arqBin);

  BinarioNaTela(nomeArqBin);
}


// Função auxiliar para buscas
void imprimir_reg_dado(RegistroDado *r){
  // esses dados nunca podem ser nulos, por isso, não serão tratados
  printf("%d ", r->codEstacao);
  printf("%s ", r->nomeEstacao);

  if (r->codLinha == -1) printf("NULO ");
  else printf("%d ", r->codLinha);

  if (strcmp(r->nomeLinha, "") == 0) printf("NULO ");
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


// Funcionalidade 2
void buscar_todos_reg_bin(){
  char nomeArqBin[100];
  scanf("%s", nomeArqBin);

  // abrir arquivo binário para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  RegistroCabecalho *h = ler_reg_cab_bin(arqBin);
  // dá erro caso o ponteiro seja NULL ou o arquivo esteja inconsistente
  if (h == NULL) {
    printf("Registro inexistente.\n");
    fclose(arqBin);
    return;
  }

  while (check_eof(arqBin)){
    RegistroDado *r = ler_reg_dado_bin(arqBin);

    // verificando se o registro está logicamente removido
    // tava com a mensagem de Registro inexistente, mas tirei pq no runcodes não aparece
    if (r->removido == '0') imprimir_reg_dado(r);
    
    free_reg_dado(r);
  }

  free_reg_cab(h);
  fclose(arqBin);
}


// Função para impressão do Registro de Cabeçalho
void imprimir_reg_cab(RegistroCabecalho *h){
  printf("%c %d %d %d %d\n", h->status, h->topo, h->proxRRN, h->nroEstacoes, h->nroParesEstacoes);
}


// Função para buscar o Registro de Cabeçalho
void buscar_reg_cab_bin(){
  char nomeArqBin[100];
  scanf("%s", nomeArqBin);

  // abrir arquivo binário para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // mover cursor para o início do arquivo
  fseek(arqBin, 0, SEEK_SET);

  RegistroCabecalho *h = ler_reg_cab_bin(arqBin);
  if (h == NULL) printf("Registro inexistente.\n");
  imprimir_reg_cab(h);

  free_reg_cab(h);
  fclose(arqBin);
}


// Função disponibilizada pelo monitor
void ScanQuoteString(char *str) {
    char R;

    while ((R = getchar()) != EOF && isspace(R))
        ; // ignorar espaços, \r, \n...

    if (R == 'N' || R == 'n') { // campo NULO
        getchar();
        getchar();
        getchar();       // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    } else if (R == '\"') {
        if (scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar();         // ignorar aspas fechando
    } else if (R != EOF) { // vc tá tentando ler uma string que não tá entre
                           // aspas! Fazer leitura normal %s então, pois deve
                           // ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    } else { // EOF
        strcpy(str, "");
    }
}


// Função auxiliar para verificar se o valor é NULO
int verificar_nulo(char *valor){
  if (strcmp(valor, "NULO") == 0) return -1;
  return atoi(valor);
}


// Funcionalidade 3
void buscar_reg_filtro(){
  char nomeArqBin[100];
  int quantBusca; 
  int quantPar; // armazena quantos pares o usuário quer
  
  // arrays para guardar os dados que devem ser filtrados
  char nomesCampos[100][100];
  char valoresCampos[100][100];

  scanf("%s %d", nomeArqBin, &quantBusca);

  // abrir arquivo binário para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  RegistroCabecalho *h = ler_reg_cab_bin(arqBin);
  // dá erro caso o ponteiro seja NULL ou o arquivo esteja inconsistente
  if (h == NULL) {
    printf("Registro inexistente.\n");
    fclose(arqBin);
    return;
  }

  // loop para buscar de acordo com a quantidade desejada
  for (int i = 0; i < quantBusca; i++){
    scanf("%d", &quantPar); 

    for (int j = 0; j < quantPar; j++){
      scanf("%s", nomesCampos[j]);

      if (strcmp(nomesCampos[j], "nomeEstacao") == 0 ||
          strcmp(nomesCampos[j], "nomeLinha") == 0
      ){
        ScanQuoteString(valoresCampos[j]); // se for string
      } else {
        scanf("%s", valoresCampos[j]);  // se for int
      }

    }

    // mover para o byte 17 para buscar nos dados
    fseek(arqBin, 17, SEEK_SET);

    int encontrou_algum = 0; // para ver se o registro foi encontrado ou não

    // fazer busca até o final do arquivo
    while (check_eof(arqBin)){
      RegistroDado *r = ler_reg_dado_bin(arqBin);

      // verificando se o registro está logicamente removido
      if (r != NULL && r->removido == '0'){
        int achou = 1; // para verificar se bate com todos os dados especificados, se não mudar, achou

        for (int b = 0; b < quantPar; b++){

          if (strcmp(nomesCampos[b], "codEstacao") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->codEstacao) achou = 0;
          }

          else if (strcmp(nomesCampos[b], "nomeEstacao") == 0){
            if (strcmp(valoresCampos[b], r->nomeEstacao) != 0){
              achou = 0;
            }
          }

          else if (strcmp(nomesCampos[b], "codLinha") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->codLinha) achou = 0;
          }

          else if (strcmp(nomesCampos[b], "nomeLinha") == 0){
            // se usuário buscou por NULO
            if (strcmp(valoresCampos[b], "") == 0){
              // se o registro tem nome, não serve pois é NULO a busca
              if (r->nomeLinha != NULL) achou = 0;
            }
            // se buscou por um nome real
            else {
              if (r->nomeLinha == NULL || strcmp(valoresCampos[b], r->nomeLinha) != 0)
                achou = 0;
            }
          }

          else if (strcmp(nomesCampos[b], "codProxEstacao") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->codProxEstacao) achou = 0;
          }

          else if (strcmp(nomesCampos[b], "distProxEstacao") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->distProxEstacao) achou = 0;
          }

          else if (strcmp(nomesCampos[b], "codLinhaIntegra") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->codLinhaIntegra) achou = 0;
          }
            
          else if (strcmp(nomesCampos[b], "codEstIntegra") == 0){
            if (verificar_nulo(valoresCampos[b]) != r->codEstIntegra) achou = 0;
          }

          // se já não atende a algum filtro, já para
          if (!achou) break;
        }

        if (achou){
          imprimir_reg_dado(r);
          encontrou_algum = 1;
        }
      } 

      free_reg_dado(r);
    }

    if (!encontrou_algum) printf("Registro inexistente.\n");

    // pular linha entre as buscas, menos no final
    if (i < quantBusca - 1) printf("\n");
  }
  
  free_reg_cab(h);
  fclose(arqBin);
}


// Funcionalidade 4
void buscar_reg_RRN(){
  char nomeArqBin[100];
  int rrn;

  // entrada dos dados desejados
  scanf("%s %d", nomeArqBin, &rrn);

  // abrir arquivo bin para leitura
  FILE *arqBin = fopen(nomeArqBin, "rb");
  if (arqBin == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  RegistroCabecalho *h = ler_reg_cab_bin(arqBin);
  // dá erro caso o ponteiro seja NULL ou o arquivo esteja inconsistente
  // verificando se esse RRN existe nos registros
  if (h == NULL || rrn >= h->proxRRN || rrn < 0) {
    printf("Registro inexistente.\n");
    fclose(arqBin);
    return;
  }

  // calculando o byte que deve ser buscado
  int byteOffSet = 80 * rrn + 17;
  fseek(arqBin, byteOffSet, SEEK_SET);

  RegistroDado *r = ler_reg_dado_bin(arqBin);

  // verificando se o registro está logicamente removido
  if (r == NULL || r->removido == '1'){
    printf("Registro inexistente.\n");
  } else {
    imprimir_reg_dado(r);
  }

  free_reg_dado(r);
  free_reg_cab(h);

  fclose(arqBin);
}