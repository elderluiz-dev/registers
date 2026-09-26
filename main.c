#include <stdio.h>
#include "interface.h"
#include "stack.h"

int main()
{
    int opcao;
    stack* pilha;
    init_stack(&pilha);
    limpa_terminal();
    while(1)
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            

            break;
        case 2:
            /* code for removing element */
            break;
        case 3:
            /* code for checking if stack is empty */
            break;
        case 4:
            /* code for checking stack size */
            break;
        case 5:
            /* code for exiting */
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }    
    }
    
    
    return 0;
}
