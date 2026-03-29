#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void free_reg_dados(RegistroDado* r){
  if (r->codEstacao){
    free((void*)r->codEstacao);
    r->codEstacao = NULL;
  }
}

void free_reg_cab(RegistroCabecalho* h){
  free((void*)h->status);
  free((void*)h->topo);
  free((void*)h->proxRRN);
  free((void*)h->nroEstacoes);
  free((void*)h->nroParesEstacoes);

  h->status = NULL;
  h->topo = NULL;
  h->proxRRN = NULL;
  h->nroEstacoes = NULL;
  h->nroParesEstacoes = NULL;
}