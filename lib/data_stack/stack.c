#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "8bit_reg.h"

uint8_t init_stack(stack **ptr_stack)
{
    if(*ptr_stack != NULL)
    {
        return 1;
    }
    
    *ptr_stack = malloc(sizeof(**ptr_stack));
    if(*ptr_stack == NULL)
    {
        return 1;
    }

    (*ptr_stack)->size = 0;
    (*ptr_stack)->top = NULL;

    return 0;
}

uint8_t add_stack_node(uint8_t data, stack **ptr_stack)
{
    if(check_full(*ptr_stack) == 1)
    {
        return 1;
    }
    
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        printf("Pilha bloqueada.\n");
        return 1;
    }
    
    n_stack *node = malloc(sizeof(*node));
    if(node == NULL)
    {
        return 1;
    }

    node->data = data;
    
    node->next = (*ptr_stack)->top;
    (*ptr_stack)->top = node;
    (*ptr_stack)->size++;

    return 0;
}

uint8_t remove_stack_node(stack **ptr_stack)
{
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        printf("Pilha bloqueada.\n");
        return 1;
    }
    
    if(stack_empty_verify(*ptr_stack) == 1)
    {
        return 1;
    }

    n_stack *novo_top = (*ptr_stack)->top->next;
    free((*ptr_stack)->top);
    (*ptr_stack)->top = novo_top;
    (*ptr_stack)->size--;
    
    if((*ptr_stack)->size < 5)
    {
        _INTERNAL_SETSTATUS_LIFO_NFULL();
    }

    return 0;
}

uint8_t stack_empty_verify(stack *ptr_stack)
{
    if(ptr_stack == NULL || ptr_stack->top == NULL)
    {
        printf("Pilha vazia!\n");
        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

uint8_t clear_stack(stack **ptr_stack)
{
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        printf("Pilha bloqueada.\n");
        return 1;
    }

    if(stack_empty_verify(*ptr_stack) == 1)
    {
        return 1;
    }
    
    while((*ptr_stack)->size != 0)
    {
        remove_stack_node(ptr_stack);
    }

    free(*ptr_stack);
    *ptr_stack = NULL;

    printf("Pilha esvaziada.");

    return 0;
}

uint8_t check_full(stack *ptr_stack)
{
    if(ptr_stack->size == 5)
    {
        _INTERNAL_SETSTATUS_LIFO_FULL();
        return 1;
    }

    return 0;
}

