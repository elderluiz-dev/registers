#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void init_stack(stack **pilha){
    *pilha = malloc(sizeof(**pilha));
    if (pilha == NULL){
        return;
    }

    printf("Pilha inicializada com sucesso!\n");
}

void add_stack_node(){
    
}