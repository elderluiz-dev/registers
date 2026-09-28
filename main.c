#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "8bit_reg.h"
#include "interface.h"

int main(){
    int opt;

    while(1)
    {
        limpa_terminal();
        int x = menu_principal();
        switch(x)
        {
        case 1:

            limpa_terminal();
            stack *pilha;
            init_stack(&pilha);
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

                    limpa_terminal();
                    add_stack_node(byte, &pilha);
                    break;

                case 2:
                    limpa_terminal();
                    remove_stack_node(&pilha);
                    break;

                case 3:
                    limpa_terminal();
                    if(stack_empty_verify(pilha) == 1){
                        break;
                    }else{
                        printf("Topo da pilha: 0x%x", pilha->topo->data);
                    }
                    break;

                case 4:
                    limpa_terminal();
                    clear_stack(&pilha);
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
                int a = menu_reg();
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