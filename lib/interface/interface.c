#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"
#include "8bit_reg.h"
#include "interface.h"

int main_menu(){
    int x;

    printf("\n===== DFC - Data Flow Controller =====\n");
    printf("1. Gerenciar pilha (LIFO)\n");
    printf("2. Gerenciar fila (FIFO)\n");
    printf("3. Gerenciar registradores\n");
    printf("0. Sair\n");
    printf("> ");

    scanf("%d%*c", &x);

    return x;    
}

int menu_stack(){
    int x;

    printf("\n===== Pilha de dados =====\n");
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

    printf("\n===== Fila de dados =====\n");
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

void init_program()
{
    int opt;
    _INIT_REGISTERS();

    while(1)
    {
        clear_terminal();
        int x = main_menu();
        switch(x)
        {
        case 1:
            if(_CHECK_LIFO_DATAFLOW() == 1){
                printf("Pilha bloqueada! Desbloqueie em <REGISTRADORES>\n");
                break;
            }

            clear_terminal();
            stack *ptr_stack;
            init_stack(&ptr_stack);
            opt = 1;
            while(opt == 1)
            {
                int a = menu_stack();
                switch(a)
                {
                case 1:
                    uint8_t byte;
                    unsigned int temp;
                    printf("Digite o dado para empilhar: ");
                    scanf("%u", &temp);
                    byte = (uint8_t)temp;

                    clear_terminal();
                    add_stack_node(byte, &ptr_stack);
                    break;

                case 2:
                    clear_terminal();
                    remove_stack_node(&ptr_stack);
                    break;

                case 3:
                    clear_terminal();
                    if(stack_empty_verify(ptr_stack) == 1){
                        break;
                    }else{
                        printf("Topo da pilha: 0x%x", ptr_stack->top->data);
                    }
                    break;

                case 4:
                    clear_terminal();
                    clear_stack(&ptr_stack);
                    break;

                case 0:
                    opt = 0;
                    break;

                default:
                    printf("Opção inválida.\n");
                    break;
                }
            }
            break;

        case 2:
            clear_terminal();
            if(_CHECK_FIFO_DATAFLOW() == 1){
                printf("Fila bloqueada! Desbloqueie em <REGISTRADORES>\n");
                break;
            }

            opt = 1;
            while(opt == 1)
            {
                int a = menu_queue();
                switch(a)
                {
                case 0:
                    opt = 0;
                    break;
                
                default:
                    printf("Opção inválida.\n");
                    break;
                }
            }
            break;

        case 3:

            opt = 1;
            while(opt == 1)
            {
                clear_terminal();
                printf("DATA0_CTRL:\n");
                printf("| ");

                for(int i = 7; i >= 0; i--)
                {
                    uint8_t bit = ((DATA0->CTRL >> i) & 1);
                    printf("%d | ", bit);
                }

                printf("\n\nDATA0_STATUS:\n");
                printf("| ");

                for(int i = 7; i >= 0; i--)
                {
                    uint8_t bit = ((DATA0->STATUS >> i) & 1);
                    printf("%d | ", bit);
                }

                printf("\n");

                int a = menu_reg();
                switch(a)
                {
                case 1:
                    if(_CHECK_FIFO_DATAFLOW() == 1){
                        _FIFO_UNLOCK_DATAFLOW();    
                    }else{
                        _FIFO_BLOCK_DATAFLOW();
                    }

                    break;

                case 2:
                    if(_CHECK_LIFO_DATAFLOW() == 1){
                        _LIFO_UNLOCK_DATAFLOW();    
                    }else{
                        _LIFO_BLOCK_DATAFLOW();
                    }

                    break;

                case 0:
                    opt = 0;
                    break;

                default:
                    printf("Opção inválida.\n");
                    break;
                }
            }
            break;

        case 0:
            printf("Programa encerrado pelo usuário\n");
            return;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }
}