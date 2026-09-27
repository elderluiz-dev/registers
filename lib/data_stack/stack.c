#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "8bit_reg.h"

void init_stack(stack **pilha){
    *pilha = malloc(sizeof(**pilha));
    if(*pilha == NULL){
        return;
    }

    (*pilha)->tamanho = 0;
    (*pilha)->topo = NULL;
}

void add_stack_node(uint8_t data, stack **pilha){
    n_stack *node = malloc(sizeof(*node));
    if(node == NULL){
        return;
    }

    node->data = data;
    
    node->prox = (*pilha)->topo;
    (*pilha)->topo = node;
    (*pilha)->tamanho++;
}

void remove_stack_node(stack **pilha){
    if(*pilha == NULL || (*pilha)->topo == NULL){
        return;
    }

    n_stack *novo_topo = (*pilha)->topo->prox;
    free((*pilha)->topo);
    (*pilha)->topo = novo_topo;
    (*pilha)->tamanho--;
}

void stack_empty_verify(stack *pilha){
    if(pilha == NULL || pilha->topo == NULL){
        printf("Lista vazia!\n");
    }else {
        printf("Lista não vazia!\n");
    }

    return;
}

void clear_stack(stack **pilha){
    while((*pilha)->tamanho != 0){
        remove_stack_node(pilha);
    }

    free(*pilha);

    return;
}

int main(){
    stack *pilha;
    uint8_t data1 = 0x12U;
    uint8_t data2 = 0x1FU;
    uint8_t data3 = 0xF3U;


    // iniciando stack    
    printf("Iniciando stack...\n");
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        init_stack(&pilha);    
    }
    printf("Stack iniciada!\n");


    // adicionando item na stack
    printf("Adicionando item na stack...\n");
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        add_stack_node(data1, &pilha);
    }
    printf("Item adicionado!...\n");
    printf("Topo da pilha: 0x%x\n", pilha->topo->data);

    printf("Adicionando item na stack...\n");
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        add_stack_node(data2, &pilha);
    }
    printf("Item adicionado!...\n");
    printf("Topo da pilha: 0x%x\n", pilha->topo->data);

    printf("Adicionando item na stack...\n");
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        add_stack_node(data3, &pilha);
    }
    printf("Item adicionado!...\n");
    printf("Topo da pilha: 0x%x\n", pilha->topo->data);


    // removendo topo da stack
    printf("Removendo topo da stack...\n");
    
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        remove_stack_node(&pilha);
    }
    printf("Item removido!\n");
    printf("Topo da pilha: 0x%x\n", pilha->topo->data);


    // verificando se a stack está vazia
    stack_empty_verify(pilha);


    // esvaziando stack
    printf("Limpando stack...\n");
    if(_CHECK_LIFO_DATAFLOW() == 1){
        printf("Lista bloqueada\n");
    }else{
        clear_stack(&pilha);
    }
    printf("Stack esvaziada!\n");

    return 0;
}