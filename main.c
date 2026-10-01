#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "8bit_reg.h"
#include "interface.h"

int main(){
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
                    printf("Byte a ser adicionado: \n");
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
                printf("REGISTRADOR: %u\n", DATA0->CTRL);
                printf("FIFO: %u | LIFO: %u\n", _CHECK_FIFO_DATAFLOW(), _CHECK_LIFO_DATAFLOW());

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
            return 0;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }

    return 0;
}