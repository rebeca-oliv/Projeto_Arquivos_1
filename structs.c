#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void free_reg_cab(RegistroCabecalho* h){
  free(h);
}

void free_reg_dado(RegistroDado* r){
  if (r->nomeEstacao != NULL) {
    free(r->nomeEstacao); 
    r->nomeEstacao = NULL;
  }
  if (r->nomeLinha != NULL) {
    free(r->nomeLinha);
    r->nomeLinha = NULL;
  }

}