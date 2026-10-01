#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "8bit_reg.h"

int main_menu(){
    int x;

    printf("\n===== SIMULADOR DE REGISTRADOR =====\n");
    printf("1. Gerenciar fila (FIFO)\n");
    printf("2. Gerenciar pilha (LIFO)\n");
    printf("3. Gerenciar registradores\n");
    printf("0. Sair\n");
    printf("> ");

    scanf("%d%*c", &x);

    return x;    
}

int menu_stack(){
    int x;

    printf("\n===== PILHA =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Verificar pilha (topo)\n");
    printf("4. Limpar pilha\n");
    printf("0. Voltar\n");
    printf("> ");
    
    scanf("%d%*c", &x);

    return x;
}

int menu_queue(){
    int x;

    printf("\n===== FILA =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Verificar fila (inicio e fim)\n");
    printf("4. Limpar fila\n");
    printf("0. Voltar\n");
    printf("> ");
    
    scanf("%d%*c", &x);

    return x;
}

int menu_reg(){
    int x;

    printf("\n===== REGISTRADORES =====\n");
    if(_CHECK_FIFO_DATAFLOW() == 1)
    {
        printf("1. Desbloquear fila\n");    
    }
    else
    {
        printf("1. Bloquear fila\n");
    }
    
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        printf("2. Desbloquear pilha\n");    
    }
    else
    {
        printf("2. Bloquear pilha\n");
    }
    
    printf("0. Voltar\n");
    printf("> ");
    
    scanf("%d%*c", &x);

    return x;
}

void clear_terminal(){
    system("clear");
}