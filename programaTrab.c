/*
Karen Nanamy Kamo - NUSP: 15495932 
Rebeca de Oliveira Silva - NUSP: 11963923
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ler_arq.h"
#include "escrever_arq.h"
#include "structs.h"
#include "funcionalidades.h"

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

  switch (opcao){
    case 1:
      criar_arq_bin();
      break;

    case 2:
      buscar_todos_reg_bin();
      break;
    
    case 3:
      buscar_reg_filtro();
      break;

    case 4:
      buscar_reg_RRN();
      break;

    default:
      printf("Opção inválida.\n");
  }
 

  return 0;
}