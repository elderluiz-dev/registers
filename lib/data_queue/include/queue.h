#pragma once

#include <stdint.h>

typedef struct node_queue {
    uint8_t data;
    struct node_queue *prox;
} n_queue;

typedef struct {
    int size;
    n_queue *inicio;
    n_queue *fim;
} queue;

uint8_t init_queue(queue **ptr_queue);
uint8_t add_queue_node(queue *ptr_queue, uint8_t data);
uint8_t remove_queue_node(queue *ptr_queue);
uint8_t check_queue(queue *ptr_queue);
uint8_t clear_queue(queue **ptr_queue);

uint8_t check_full_queue(queue *ptr_queue);