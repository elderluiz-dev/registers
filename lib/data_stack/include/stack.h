#pragma once

#include <stdint.h>

typedef struct node_stack {
    uint8_t data;
    struct node_stack* next;
} n_stack;

typedef struct stack {
    int size;
    n_stack* top;
} stack;

// must-have
uint8_t init_stack(stack **ptr_stack);
uint8_t add_stack_node(uint8_t data, stack **ptr_stack);
uint8_t remove_stack_node(stack **ptr_stack);
uint8_t stack_empty_verify(stack *ptr_stack);
uint8_t clear_stack(stack **ptr_stack);

// extra
uint8_t check_full(stack *ptr_stack);