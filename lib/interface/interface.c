#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"
#include "8bit_reg.h"
#include "interface.h"
#include "config.h"

int main_menu()
{
    int x;

    printf("\n" BLUE_STR "=====" RESET " " PURPLE_BOLD "DFC-8" RESET " - " WHITE_STR "Data Flow Controller" RESET " " BLUE_STR "=====" RESET "\n");
    printf(WHITE_STR "1." RESET " Gerenciar Pilha (" WHITE_STR "LIFO" RESET ")\n");
    printf(WHITE_STR "2." RESET " Gerenciar Fila  (" WHITE_STR "FIFO" RESET ")\n");
    printf(WHITE_STR "3." RESET " Gerenciar Registradores\n\n");
    printf(RED_STR "0." RED " Sair" RESET "\n");
    printf(BLUE_STR "> " RESET);

    scanf("%d%*c", &x);

    return x;    
}

int menu_stack()
{
    int x;

    printf("\n" BLUE_STR "=====" RESET " " WHITE_STR "Pilha de dados" RESET " " BLUE_STR "=====" RESET "\n");
    printf(WHITE_STR "1." RESET " Adicionar item\n");
    printf(WHITE_STR "2." RESET " Remover item\n");
    printf(WHITE_STR "3." RESET " Verificar topo da pilha\n");
    printf(WHITE_STR "4." RESET " Limpar pilha\n\n");
    printf(YELLOW_STR "0." YELLOW " Voltar" RESET "\n");
    printf(BLUE_STR "> " RESET);
    
    scanf("%d%*c", &x);

    return x;
}

int menu_queue()
{
    int x;

    printf("\n" BLUE_STR "=====" RESET " " WHITE_STR "Fila de dados" RESET " " BLUE_STR "=====" RESET "\n");
    printf(WHITE_STR "1." RESET " Adicionar item\n");
    printf(WHITE_STR "2." RESET " Remover item\n");
    printf(WHITE_STR "3." RESET " Verificar inicio e fim da fila\n");
    printf(WHITE_STR "4." RESET " Limpar fila\n\n");
    printf(YELLOW_STR "0." YELLOW " Voltar" RESET "\n");
    printf(BLUE_STR "> " RESET);
    
    scanf("%d%*c", &x);

    return x;
}

int menu_reg()
{
    int x;

    printf("\n" BLUE_STR "=====" RESET " " WHITE_STR "Registradores" RESET " " BLUE_STR "=====" RESET "\n");
    if(_CHECK_LIFO_DATAFLOW() == 1)
    {
        printf(WHITE_STR "1." RESET " " GREEN "Desbloquear pilha" RESET "\n");    
    }
    else
    {
        printf(WHITE_STR "1." RESET " " RED "Bloquear pilha" RESET "\n");
    }

    if(_CHECK_FIFO_DATAFLOW() == 1)
    {
        printf(WHITE_STR "2." RESET " " GREEN "Desbloquear fila" RESET "\n\n");    
    }
    else
    {
        printf(WHITE_STR "2." RESET " " RED "Bloquear fila" RESET "\n\n");
    }
    
    printf(YELLOW_STR "0." YELLOW " Voltar" RESET "\n");
    printf(BLUE_STR "> " RESET);
    
    scanf("%d%*c", &x);

    return x;
}

void clear_terminal()
{
    system("clear");
}

void init_program()
{
    _INIT_REGISTERS();
    clear_terminal();

    int opt;

    stack *ptr_stack = NULL;
    queue *ptr_queue = NULL;

    while(1)
    {
        int x = main_menu();
        switch(x)
        {
            case 1:
            {
                clear_terminal();
                if(_CHECK_LIFO_DATAFLOW() == 1)
                {
                    printf(RED "Pilha bloqueada!" RESET " Desbloqueie em " YELLOW_STR "<Registradores>" RESET "\n");
                    break;
                }
                
                init_stack(&ptr_stack);

                opt = 1;
                while(opt == 1)
                {
                    int a = menu_stack();
                    switch(a)
                    {
                        case 1:
                        {
                            if(ptr_stack == NULL)
                            {
                                init_stack(&ptr_stack);
                            }

                            uint8_t byte;
                            unsigned int temp;
                            printf("Digite o dado para empilhar: ");
                            scanf("%u", &temp);
                            byte = (uint8_t)temp;

                            clear_terminal();
                            add_stack_node(byte, &ptr_stack);
                            break;
                        }

                        case 2:
                        {
                            clear_terminal();
                            remove_stack_node(&ptr_stack);
                            break;
                        }

                        case 3:
                        {
                            clear_terminal();
                            if(stack_empty_verify(ptr_stack) == 1){
                                break;
                            }
                            else
                            {
                                printf("A fila possui" GREEN " %d " RESET "elemento(s)\n", ptr_stack->size);
                                printf("Topo da pilha: " GREEN "0x%X\n" RESET, ptr_stack->top->data);
                            }
                            break;
                        }

                        case 4:
                        {
                            clear_terminal();
                            clear_stack(&ptr_stack);
                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            clear_terminal();
                            break;
                        }

                        default:
                        {
                            clear_terminal();
                            printf(RED "A opção selecionada é inválida." RESET "\n");
                            break;
                        }
                    }
                }

                break;
            }

            case 2:
            {
                clear_terminal();
                if(_CHECK_FIFO_DATAFLOW() == 1)
                {
                    printf(RED "Fila bloqueada!" RESET " Desbloqueie em " YELLOW_STR "<Registradores>" RESET "\n");
                    break;
                }

                init_queue(&ptr_queue);

                opt = 1;
                while(opt == 1)
                {
                    int a = menu_queue();
                    switch(a)
                    {
                        case 1:
                        {
                            if(ptr_queue == NULL)
                            {
                                init_queue(&ptr_queue);
                            }

                            uint8_t byte;
                            unsigned int temp;

                            printf("Digite o dado para adicionar à fila: ");
                            scanf("%u", &temp);
                            byte = (uint8_t)temp;

                            clear_terminal();
                            add_queue_node(ptr_queue, byte);

                            break;
                        }

                        case 2:
                        {
                            clear_terminal();
                            remove_queue_node(ptr_queue);
                            break;
                        }

                        case 3:
                        {
                            clear_terminal();
                            if(check_queue(ptr_queue)) break;

                            printf("Inicio da fila: " GREEN "0x%X" RESET "\n", ptr_queue->inicio->data);
                            printf("Fim da fila: " GREEN "0x%X" RESET "\n", ptr_queue->fim->data);

                            break;
                        }

                        case 4:
                        {
                            clear_terminal();
                            clear_queue(&ptr_queue);
                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            clear_terminal();
                            break;
                        }

                        default:
                        {
                            clear_terminal();
                            printf(RED "A opção selecionada é inválida." RESET "\n");
                            break;
                        }
                    }
                }

                break;
            }

            case 3:
            {

                int reg_invalid = 0;

                opt = 1;
                while(opt == 1)
                {
                    clear_terminal();
                    printf(WHITE_STR "DATA0_CTRL:" RESET "\n");
                    printf("| ");

                    for(int i = 7; i >= 0; i--)
                    {
                        uint8_t bit = ((DATA0->CTRL >> i) & 1);
                        if(bit == 1)
                        {
                            printf(GREEN "%d" RESET " | ", bit);
                        }
                        else
                        {
                            printf(RED "%d" RESET " | ", bit);
                        }
                    }

                    printf("\n\n" WHITE_STR "DATA0_STATUS:" RESET "\n");
                    printf("| ");

                    for(int i = 7; i >= 0; i--)
                    {
                        uint8_t bit = ((DATA0->STATUS >> i) & 1);
                        if(bit == 1)
                        {
                            printf(GREEN "%d" RESET " | ", bit);
                        }
                        else
                        {
                            printf(RED "%d" RESET " | ", bit);
                        }
                    }

                    printf("\n");

                    if(reg_invalid == 1)
                    {
                        printf(RED "\nA opção selecionada é inválida." RESET "\n");
                        reg_invalid = 0;
                    }

                    int a = menu_reg();
                    switch(a)
                    {
                        case 1:
                        {
                            if(_CHECK_LIFO_DATAFLOW() == 1)
                            {
                                _LIFO_UNLOCK_DATAFLOW();    
                            }
                            else
                            {
                                _LIFO_BLOCK_DATAFLOW();
                            }

                            break;   
                        }

                        case 2:
                        {
                            if(_CHECK_FIFO_DATAFLOW() == 1)
                            {
                                _FIFO_UNLOCK_DATAFLOW();    
                            }
                            else
                            {
                                _FIFO_BLOCK_DATAFLOW();
                            }

                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            clear_terminal();
                            break;
                        }

                        default:
                        {
                            clear_terminal();
                            reg_invalid = 1;
                            break;
                        }
                    }
                }

                break;
            }

            case 0:
            {
                clear_stack(&ptr_stack);
                clear_queue(&ptr_queue);
                clear_terminal();
                
                printf(GREEN "\nPrograma encerrado pelo usuário" RESET "\n");
                return;
            }

            default:
            {
                clear_terminal();
                printf(RED "\nA opção selecionada é inválida." RESET "\n");
                break;
            }
        }
    }
}