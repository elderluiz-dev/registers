#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../reg/8bit_reg.h"

uint8_t init_queue(queue **fila)
{
    *fila = (queue *)malloc(sizeof(**fila));

    if(*fila == NULL)
    {
        printf("Erro na inicialização da fila.\n");
        return 1;
    }

    (*fila)->size = 0;
    (*fila)->inicio = NULL;
    (*fila)->fim = NULL;
    return 0;
}

uint8_t add_queue_node(queue *fila, uint8_t data)
{
    if(fila == NULL)
    {
        printf("A fila ainda não foi iniciada.");
        return 1;
    }
    if(_CHECK_FIFO_DATAFLOW() || check_full_queue(fila))
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

    if(fila->inicio == NULL)
    {
        fila->inicio = new;
        fila->fim = new;
        fila->size++;
        check_full_queue(fila);

        return 0;
    }

    fila->fim->prox = new;
    fila->fim = new;
    fila->size++;
    check_full_queue(fila);

    return 0;
}

uint8_t remove_queue_node(queue *fila)
{
    if(fila == NULL || fila->size == 0)
    {
        printf("A fila esta vazia.");
        return 1;
    }
    if(_CHECK_FIFO_DATAFLOW())
    {
        printf("A fila está bloqueada!\n");
        return 1;
    }

    if(fila->size == 1)
    {
        free(fila->inicio);
        fila->inicio = NULL;
        fila->fim = NULL;

        fila->size--;
        return 0;
    }

    n_queue *aux = fila->inicio;
    fila->inicio = aux->prox;
    free(aux);
    fila->size--;

    if(fila->size < 5)
    {
        _INTERNAL_SETSTATUS_FIFO_NFULL();
    }

    return 0;
}

uint8_t check_queue(queue *fila)
{
    if(fila == NULL || fila->size == 0)
    {
        printf("A fila esta vazia.");
        return 1;
    }
    printf("A fila possui %d elementos", fila->size);
    
    return 0;
}

uint8_t clear_queue(queue **fila)
{
    if(*fila == NULL)
    {
        printf("A fila ainda não foi iniciada.");
        return 1;
    }
    if(_CHECK_FIFO_DATAFLOW())
    {
        printf("A fila está bloqueada!\n");
        return 1;
    }

    while((*fila)->size != 0)
    {
        remove_queue_node(*fila);
    }

    free(*fila);
    return 0;
}

uint8_t check_full_queue(queue *fila)
{
    if(fila->size == 5)
    {
        _INTERNAL_SETSTATUS_FIFO_FULL();
        return 1;
    }

    return 0;
}
