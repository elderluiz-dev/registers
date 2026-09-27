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

    while((*fila)->size != 0)
    {
        remove_queue_node(*fila);
    }

    free(*fila);
    return;
}
/*
int main(){
    queue *fila;
    uint8_t data1 = 0x12U;
    uint8_t data2 = 0x1FU;
    uint8_t data3 = 0xF3U;


    // iniciando stack    
    printf("Iniciando fila...\n");
    init_queue(&fila);
    printf("Fila iniciada!\n");


    // adicionando item na stack
    printf("Adicionando item na fila...\n");
    add_queue_node(fila, data1);
    printf("Item adicionado!...\n");
    printf("Topo da fila: 0x%x\n", fila->inicio->data);

    printf("Adicionando item na fila...\n");
    add_queue_node(fila, data2);
    printf("Item adicionado!...\n");
    printf("Fim da fila: 0x%x\n", fila->fim->data);

    printf("Adicionando item na fila...\n");
    add_queue_node(fila, data3);
    printf("Item adicionado!...\n");
    printf("Fim da fila: 0x%x\n", fila->fim->data);


    // removendo topo da stack
    printf("Removendo topo da fila...\n");

    remove_queue_node(fila);
    printf("Item removido!\n");
    printf("Fim da fila: 0x%x\n", fila->fim->data);


    // verificando se a stack está vazia
    check_queue(fila);
    printf("\n");


    // esvaziando stack
    printf("Limpando fila...\n");
    clear_queue(&fila);
    printf("Fila esvaziada!\n");

    return 0;
}
*/