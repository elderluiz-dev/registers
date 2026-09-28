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
        int x = menu_principal();
        switch(x)
        {
        case 1:

            opt = 1;
            while(opt == 1)
            {
                int a = menu_stack();
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