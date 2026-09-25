#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int menu(){
    int opcao;
    printf("Escolha uma opção:\n");
    printf("1 - Inserir elemento na pilha\n");
    printf("2 - Remover elemento da pilha\n");
    printf("3 - Verificar se a pilha está vazia\n");
    printf("4 - Verificar o tamanho da pilha\n");
    printf("5 - Sair\n");
    scanf("%d", &opcao);
    return opcao;
}

void limpa_terminal(){
    system("clear");
}