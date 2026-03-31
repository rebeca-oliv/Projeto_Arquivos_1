#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ler_arq.h"
#include "escrever_arq.h"
#include "structs.h"
#include "funcionalidades.h"

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

RegistroCabecalho le_reg_cab_bin(FILE* arq) {
    RegistroCabecalho h;
    
    fseek(arq, 0, SEEK_SET);
    
    fread(&h.status, sizeof(char), 1, arq);
    fread(&h.topo, sizeof(int), 1, arq);
    fread(&h.proxRRN, sizeof(int), 1, arq);
    fread(&h.nroEstacoes, sizeof(int), 1, arq);
    fread(&h.nroParesEstacoes, sizeof(int), 1, arq);
    
    return h;
}

int main(){
  int opcao;
  scanf("%d", &opcao);

  char nomeArq[100];
  char nomeArqBin[100];

  if (opcao == 1){
    scanf("%s %s", nomeArq, nomeArqBin);
    criar_arq_bin(nomeArq, nomeArqBin);
    BinarioNaTela(nomeArqBin);
  }
  else if (opcao == 2){
    scanf("%s", nomeArqBin);
    mostrar_todos_reg_bin(nomeArqBin);
  } 
  else if (opcao == 3){
    char nome[100] = "estacoes.bin";
    BinarioNaTela(nome);
  } 
  else if (opcao == 4){
    scanf("%s", nomeArqBin);
    mostrar_reg_cab_bin(nomeArqBin);
  }
  else {
    printf("Opção inválida.\n");
  }

  return 0;
}