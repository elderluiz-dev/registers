#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "8bit_reg.h"
#include "config.h"

uint8_t init_queue(queue **ptr_queue)
{
    if(*ptr_queue != NULL)
    {
        return 1;
    }
    
    *ptr_queue = (queue *)malloc(sizeof(**ptr_queue));
    if(*ptr_queue == NULL)
    {
        printf("\n" RED "Erro de alocação de memória: init_queue.\n" RESET);
        return 1;
    }

    (*ptr_queue)->size = 0;
    (*ptr_queue)->inicio = NULL;
    (*ptr_queue)->fim = NULL;

    return 0;
}

uint8_t add_queue_node(queue *ptr_queue, uint8_t data)
{
    if(ptr_queue == NULL)
    {
        printf(RED "A Fila não foi iniciada ou está vazia!\n" RESET);
        return 1;
    }
 
    if(check_full_queue(ptr_queue))
    {
        printf(RED "A Fila está cheia!\n" RESET);
        return 1;
    }

    n_queue *new = (n_queue *)malloc(sizeof(*new));
    if(new == NULL)
    {
        printf("\n" RED "Erro de alocação de memória: add_queue_node.\n" RESET);
        return 1;
    }

    new->data = data;
    new->prox = NULL;

    if(ptr_queue->inicio == NULL)
    {
        ptr_queue->inicio = new;
        ptr_queue->fim = new;
        ptr_queue->size++;
        check_full_queue(ptr_queue);

        printf(GREEN "Dado adicionado com sucesso!\n" RESET);
        return 0;
    }

    ptr_queue->fim->prox = new;
    ptr_queue->fim = new;
    ptr_queue->size++;
    check_full_queue(ptr_queue);

    printf(GREEN "Dado adicionado com sucesso!\n" RESET);
    return 0;
}

uint8_t remove_queue_node(queue *ptr_queue)
{
    if(ptr_queue == NULL || ptr_queue->size == 0)
    {
        printf(RED "A Fila está vazia.\n" RESET);
        return 1;
    }

    if(ptr_queue->size == 1)
    {
        free(ptr_queue->inicio);
        ptr_queue->inicio = NULL;
        ptr_queue->fim = NULL;

        ptr_queue->size--;
        
        printf(GREEN "Dado removido com sucesso! Fila está vazia.\n" RESET);
        return 0;
    }

    n_queue *aux = ptr_queue->inicio;
    ptr_queue->inicio = aux->prox;
    free(aux);
    ptr_queue->size--;

    if(ptr_queue->size < 5)
    {
        _INTERNAL_SETSTATUS_FIFO_NFULL();
    }

    printf(GREEN "Dado removido com sucesso!\n" RESET);
    return 0;
}

uint8_t check_queue(queue *ptr_queue)
{
    if(ptr_queue == NULL || ptr_queue->size == 0)
    {
        printf(RED "A Fila está vazia.\n" RESET);
        return 1;
    }
 
    printf("A fila possui" GREEN " %d " RESET "elemento(s)\n", ptr_queue->size);
    
    return 0;
}

uint8_t clear_queue(queue **ptr_queue)
{
    if(*ptr_queue == NULL || (*ptr_queue)->size == 0)
    {
        printf(RED "A fila não foi iniciada ou está vazia!\n" RESET);
        return 1;
    }

    while((*ptr_queue)->size != 0)
    {
        if((*ptr_queue)->size == 1)
        {
            free((*ptr_queue)->inicio);
            (*ptr_queue)->inicio = NULL;
            (*ptr_queue)->fim = NULL;

            (*ptr_queue)->size--;
            
            break;
        }

        n_queue *aux = (*ptr_queue)->inicio;
        (*ptr_queue)->inicio = aux->prox;
        free(aux);
        (*ptr_queue)->size--;

        if((*ptr_queue)->size < 5)
        {
            _INTERNAL_SETSTATUS_FIFO_NFULL();
        }
    }

    free(*ptr_queue);
    *ptr_queue = NULL;
    printf(GREEN "A fila foi esvaziada!\n" RESET);    
    return 0;
}

uint8_t check_full_queue(queue *ptr_queue)
{
    if(ptr_queue->size == 5)
    {
        _INTERNAL_SETSTATUS_FIFO_FULL();
        return 1;
    }

    return 0;
}
