#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(queue **fila)
{
    *fila = (queue *)malloc(sizeof(**fila));

    if(*fila == NULL)
    {
        printf("Erro na inicialização da fila.\n");
        return;
    }

    (*fila)->size = 0;
    (*fila)->inicio = NULL;
    (*fila)->fim = NULL;
    return;
}

void add_queue_node(queue *fila, uint8_t data)
{
    if(fila == NULL)
    {
        printf("A fila ainda não foi iniciada.");
        return;
    }

    n_queue *new = (n_queue *)malloc(sizeof(*new));
    if(new == NULL)
    {
        return;
    }

    new->data = data;
    new->prox = NULL;

    if(fila->inicio == NULL)
    {
        fila->inicio = new;
        fila->fim = new;
        fila->size++;

        return;
    }
    fila->fim->prox = new;
    fila->fim = new;
    fila->size++;

    return;
}

void remove_queue_node(queue *fila)
{
    if(fila == NULL || fila->size == 0)
    {
        printf("A fila esta vazia.");
        return;
    }

    if(fila->size == 1)
    {
        free(fila->inicio);
        fila->inicio = NULL;
        fila->fim = NULL;

        fila->size--;
        return;
    }
    n_queue *aux = fila->inicio;
    fila->inicio = aux->prox;
    free(aux);
    fila->size--;

    return;
}

void check_queue(queue *fila)
{
    if(fila == NULL || fila->size == 0)
    {
        printf("A fila esta vazia.");
        return;
    }
    printf("A fila possui %d elementos", fila->size);
    
    return;
}

void clear_queue(queue **fila)
{
    if(*fila == NULL)
    {
        printf("A fila ainda não foi iniciada.");
        return;
    }

    n_queue *node = (*fila)->inicio;
    while(node != NULL)
    {
        (*fila)->inicio = node->prox;
        free(node);
        node = (*fila)->inicio;
    }

    free(*fila);
    return;
}