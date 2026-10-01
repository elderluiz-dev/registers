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

// must-have
uint8_t init_stack(stack **pilha);
uint8_t add_stack_node(uint8_t data, stack **pilha);
uint8_t remove_stack_node(stack **pilha);
uint8_t stack_empty_verify(stack *pilha);
uint8_t clear_stack(stack **pilha);

// extra
uint8_t check_full(stack *pilha);