#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "8bit_reg.h"

uint8_t init_stack(stack **pilha){
    if(*pilha != NULL){
        printf("Lista já iniciada\n");
        return 1;
    }
    
    *pilha = malloc(sizeof(**pilha));
    if(*pilha == NULL){
        return 1;
    }

    (*pilha)->tamanho = 0;
    (*pilha)->topo = NULL;

    return 0;
}

uint8_t add_stack_node(int data, stack **pilha){
    if(check_full(*pilha) == 1){
        return 1;
    }
    
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Pilha bloqueada.\n");
        return 1;
    }
    
    n_stack *node = malloc(sizeof(*node));
    if(node == NULL){
        return 1;
    }

    node->data = data;
    
    node->prox = (*pilha)->topo;
    (*pilha)->topo = node;
    (*pilha)->tamanho++;
    printf("Item adicionado.\n");
    printf("Tamanho da lista: %d\n\n", (*pilha)->tamanho);

    return 0;
}

uint8_t remove_stack_node(stack **pilha){
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Pilha bloqueada.\n");
        return 1;
    }
    
    if(*pilha == NULL || (*pilha)->topo == NULL){
        return 1;
    }

    n_stack *novo_topo = (*pilha)->topo->prox;
    free((*pilha)->topo);
    (*pilha)->topo = novo_topo;
    (*pilha)->tamanho--;

    if((*pilha)->tamanho < 5){
        _INTERNAL_SETSTATUS_LIFO_NFULL();
    }

    return 0;
}

uint8_t stack_empty_verify(stack *pilha){
    if(pilha == NULL || pilha->topo == NULL){
        printf("Lista vazia!\n");
        return 0;
    }else {
        printf("Lista não vazia!\n");
        return 0;
    }

    return 0;
}

uint8_t clear_stack(stack **pilha){
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Pilha bloqueada.\n");
        return 1;
    }
    
    while((*pilha)->tamanho != 0){
        remove_stack_node(pilha);
    }

    free(*pilha);

    return 0;
}

 uint8_t check_full(stack *pilha){
    if(pilha->tamanho == 5){
        printf("Lista cheia.");
        _INTERNAL_SETSTATUS_LIFO_FULL();
        return 1;
    }

    printf("Lista não vazia.\n");

    return 0;
 }

