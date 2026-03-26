/*

#include <stdio.h>
// Struct criada para o Registro de Cabeçalho - topo é um ponteiro que aponta para o topo da pilha
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

  //ponteiro ou não?
  int proximo;

  // não pode ser 0 
  int codEstacao;

  // o 0 deve ser representado por -1
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;

  // se for "" o tam deve ser 0
  int tamNomeEstacao;
  // não ler o \0 no final, não pode ser o 0
  char *nomeEstacao;

  // se for "" o tam deve ser 0
  int tamNomeLinha;
  // não ler o \0 no final
  char *nomeLinha;

} RegistroDado;

int main(){
  ///////////////////////////////////////////////

  // declaração de ponteiro para  o arquivo 
  FILE *arq;
  // abertura de arquivo para leitura
  arq = fopen("estacao.csv", "r+");
  // verificando se o arquivo foi aberto
  if (arq == NULL){
    printf("Falha no processamento de arquivo");
    return 0;
  }
  // leitura de cada linha do arquivo csv
  char linha[1024];
  while (fgets(linha, sizeof(linha), arq) != NULL) {
    printf("%s", linha);
  }
  fclose(arq);

  /////////////////////////////////////////////////

  // se não existir um arquivo com esse nome, ele vai criar
  // teste para ver se está escrevendo no arquivo binário
  FILE *arqBin = fopen("estacao.bin", "wb");
  if (arqBin == NULL){
    printf("Falha no processamento de arquivo");
    return 0;
  }

  int numeros[5] = {10, 20, 30, 40, 50};
  fwrite(numeros, sizeof(int), 5, arqBin);
  fclose(arqBin);

  // teste para ver se está lendo do arquivo binário
  arqBin = fopen("estacao.bin", "rb");
  if (arqBin == NULL){
    printf("Falha no processamento de arquivo");
    return 0;
  }
  int lidos[5];
  fread(lidos, sizeof(int), 5, arqBin);
  fclose(arqBin);

  // IMPRIMINDO
  for (int i = 0; i < 5; i++) {
    printf("\n%d ", lidos[i]);
  }

  return 0;
}

*/