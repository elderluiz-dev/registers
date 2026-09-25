#pragma once

typedef struct node_stack {
    int bit;
    struct stack* prox;
} n_stack;

typedef struct stack {
    int tamanho;
    n_stack* topo;
} stack;

void init_stack(stack **pilha);
void add_stack_node();
void remove_stack_node();
void stack_query_next();
void clear_stack();
