#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "8bit_reg.h"

uint8_t init_queue(queue **ptr_queue)
{
    if(*ptr_queue != NULL)
    {
        return 1;
    }
    
    *ptr_queue = (queue *)malloc(sizeof(**ptr_queue));

    if(*ptr_queue == NULL)
    {
        printf("Erro na inicialização da fila.\n");
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
        printf("A fila ainda não foi iniciada.");
        return 1;
    }
 
    if(_CHECK_FIFO_DATAFLOW() || check_full_queue(ptr_queue))
    {
        printf("Não pode ser adicionado!\n");
        return 1;
    }

    n_queue *new = (n_queue *)malloc(sizeof(*new));
    if(new == NULL)
    {
        printf("Erro na alocação de memoria!\n");
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

        return 0;
    }

    ptr_queue->fim->prox = new;
    ptr_queue->fim = new;
    ptr_queue->size++;
    check_full_queue(ptr_queue);

    return 0;
}

uint8_t remove_queue_node(queue *ptr_queue)
{
    if(ptr_queue == NULL || ptr_queue->size == 0)
    {
        printf("A fila esta vazia.");
        return 1;
    }
 
    if(_CHECK_FIFO_DATAFLOW())
    {
        printf("A fila está bloqueada!\n");
        return 1;
    }

    if(ptr_queue->size == 1)
    {
        free(ptr_queue->inicio);
        ptr_queue->inicio = NULL;
        ptr_queue->fim = NULL;

        ptr_queue->size--;
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

    return 0;
}

uint8_t check_queue(queue *ptr_queue)
{
    if(ptr_queue == NULL || ptr_queue->size == 0)
    {
        printf("A fila esta vazia.");
        return 1;
    }
 
    printf("A fila possui %d elementos\n", ptr_queue->size);
    
    return 0;
}

uint8_t clear_queue(queue **ptr_queue)
{
    if(*ptr_queue == NULL)
    {
        printf("A fila ainda não foi iniciada.");
        return 1;
    }
 
    if(_CHECK_FIFO_DATAFLOW())
    {
        printf("A fila está bloqueada!\n");
        return 1;
    }

    while((*ptr_queue)->size != 0)
    {
        remove_queue_node(*ptr_queue);
    }

    free(*ptr_queue);
    *ptr_queue = NULL;
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
