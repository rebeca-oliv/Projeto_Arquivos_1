#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define MAX 100 // estoura a pilha, rever para saber se é suficiente
// variáveis globais ruins? 

struct  stack
{
    int dados[MAX]; 
    int num_elementos; 
};

pilha *cria_pilha(){
    pilha *topo = malloc(sizeof(pilha)); 
    
}
