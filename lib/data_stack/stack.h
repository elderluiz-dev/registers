#pragma once
#include <stdint.h>

typedef struct node_stack {
    uint8_t data;
    struct node_stack* prox;
} n_stack;

typedef struct stack {
    int tamanho;
    n_stack* topo;
} stack;

void init_stack(stack **pilha);
void add_stack_node(int data, stack **pilha);
void remove_stack_node(stack **pilha);
void stack_empty_verify(stack **pilha);
void clear_stack(stack **pilha);
