#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "8bit_reg.h"
#include "config.h"

uint8_t init_stack(stack **ptr_stack)
{
    if(*ptr_stack != NULL)
    {
        return 1;
    }
    
    *ptr_stack = malloc(sizeof(**ptr_stack));
    if(*ptr_stack == NULL)
    {
        printf("\n" RED "Erro de alocação de memória: init_stack.\n" RESET);
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
    
    // VER MELHOR DEPOIS!
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        return 1;
    }
    
    n_stack *node = malloc(sizeof(*node));
    if(node == NULL)
    {
        printf("\n" RED "Erro de alocação de memória: add_stack_node.\n" RESET);
        return 1;
    }

    node->data = data;
    
    node->next = (*ptr_stack)->top;
    (*ptr_stack)->top = node;
    (*ptr_stack)->size++;

    printf(GREEN "Dado adicionado com sucesso!\n" RESET);
    return 0;
}

uint8_t remove_stack_node(stack **ptr_stack)
{
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
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

    printf(RED "Dado removido!\n" RESET);
    return 0;
}

uint8_t stack_empty_verify(stack *ptr_stack)
{
    if(ptr_stack == NULL || ptr_stack->top == NULL)
    {
        printf(RED "A Pilha está vazia.\n" RESET);
        return 1;
    }

    return 0;
}

uint8_t clear_stack(stack **ptr_stack)
{
    if(*ptr_stack == NULL){
        printf(RED "A Pilha não foi iniciada!\n" RESET);
        return 1;
    }

    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        return 1;
    }
    
    while((*ptr_stack)->size != 0)
    {
        remove_stack_node(ptr_stack);
    }

    free(*ptr_stack);
    *ptr_stack = NULL;

    printf(GREEN "A Pilha foi esvaziada.\n" RESET);
    return 0;
}

uint8_t check_full(stack *ptr_stack)
{
    if(ptr_stack->size == 5)
    {
        printf(RED "A Pilha está cheia!\n" RESET);
        _INTERNAL_SETSTATUS_LIFO_FULL();
        return 1;
    }

    return 0;
}