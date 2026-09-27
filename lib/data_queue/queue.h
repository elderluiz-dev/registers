#pragma once
#include <stdint.h>

typedef struct node_queue 
{
    uint8_t data;
    struct node_queue *prox;
} n_queue;

typedef struct 
{
    int size;
    n_queue *inicio;
    n_queue *fim;
} queue;

void init_queue(queue **fila);
void add_queue_node(queue *fila, uint8_t data);
void remove_queue_node(queue *fila);
void check_queue(queue *fila);
void clear_queue(queue **fila);