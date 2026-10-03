#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "stack.h"
#include "queue.h"
#include "8bit_reg.h"
#include "interface.h"

data_thread *data;

int main_menu(){
    int x;
    pthread_mutex_lock(&data->mutex);
    printf("\n===== DFC-8 - Data Flow Controller =====\n");
    printf("1. Gerenciar pilha (LIFO)\n");
    printf("2. Gerenciar fila (FIFO)\n");
    printf("3. Gerenciar registradores\n");
    printf("0. Sair\n");
    printf("> ");

    scanf("%d%*c", &x);
    pthread_mutex_unlock(&data->mutex);
    return x;    
}

int menu_stack(){
    int x;
    pthread_mutex_lock(&data->mutex);
    printf("\n===== Pilha de dados =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Verificar pilha (topo)\n");
    printf("4. Limpar pilha\n");
    printf("0. Voltar\n");
    printf("> ");
    
    scanf("%d%*c", &x);
    pthread_mutex_unlock(&data->mutex); 
    return x;
}

int menu_queue(){
    int x;
    pthread_mutex_lock(&data->mutex);
    printf("\n===== Fila de dados =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Verificar fila (inicio e fim)\n");
    printf("4. Limpar fila\n");
    printf("0. Voltar\n");
    printf("> ");
    
    scanf("%d%*c", &x);
    pthread_mutex_unlock(&data->mutex);
    return x;
}

int menu_reg(){
    int x;
    pthread_mutex_lock(&data->mutex);
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
    pthread_mutex_unlock(&data->mutex);
    return x;
}

void clear_terminal(){
    system("clear");
}

void *interface_reg(void *)
{
    while (1) 
    {
        pthread_mutex_lock(&data->mutex);

        while(data->update == 0)
        {
            pthread_cond_wait(&data->cond, &data->mutex);
        }

        printf("\033[s");
        printf("\033[%d;%dH", 3, 50);
    
        printf("DATA0_CTRL:");
        printf("\033[%d;%dH", 4, 50);
        printf("| ");
        for(int i = 7; i >= 0; i--)
        {
            uint8_t bit = ((DATA0->CTRL >> i) & 1);
            printf("%d | ", bit);
        }
        
        printf("\033[%d;%dH", 5, 50);
        printf("DATA0_STATUS:");
        printf("\033[%d;%dH", 6, 50);
        printf("| ");
        for(int i = 7; i >= 0; i--)
        {
            uint8_t bit = ((DATA0->STATUS >> i) & 1);
            printf("%d | ", bit);
        }
        printf("\033[u");

        data->update = 0;
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

void notify_thread()
{
    pthread_mutex_lock(&data->mutex);
    data->update = 1;
    pthread_mutex_unlock(&data->mutex);
    pthread_cond_signal(&data->cond);

    return;
}

void init_program()
{
    int opt;
    pthread_t thread_id;
    data = (data_thread *)malloc(sizeof(*data));

    data->update = 0;
    pthread_cond_init(&data->cond, NULL);
    pthread_mutex_init(&data->mutex, NULL);

    _INIT_REGISTERS();

    pthread_create(&thread_id, NULL, interface_reg, NULL);

    while(1)
    {
        clear_terminal();

        stack *ptr_stack = NULL;
        queue *ptr_queue = NULL;

        int x = main_menu();
        switch(x)
        {
            case 1:
            {
                if(_CHECK_LIFO_DATAFLOW() == 1){
                    printf("Pilha bloqueada! Desbloqueie em <REGISTRADORES>\n");
                    break;
                }

                clear_terminal();
                notify_thread();

                init_stack(&ptr_stack);

                opt = 1;
                while(opt == 1)
                {
                    int a = menu_stack();
                    switch(a)
                    {
                        case 1:
                        {
                            
                            if(ptr_stack == NULL){
                                init_stack(&ptr_stack);
                            }

                            uint8_t byte;
                            unsigned int temp;
                            printf("Digite o dado para empilhar: ");
                            scanf("%u", &temp);
                            byte = (uint8_t)temp;

                            add_stack_node(byte, &ptr_stack);
                            clear_terminal();
                            notify_thread();

                            break;
                        }

                        case 2:
                        {
                            clear_terminal();
                            remove_stack_node(&ptr_stack);
                            notify_thread();
                            break;
                        }

                        case 3:
                        {
                            clear_terminal();
                            notify_thread();
                            if(stack_empty_verify(ptr_stack) == 1){
                                break;
                            }else{
                                printf("Topo da pilha: 0x%x", ptr_stack->top->data);
                            }
                            break;
                        }

                        case 4:
                        {
                            clear_terminal();
                            clear_stack(&ptr_stack);
                            notify_thread();
                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            break;
                        }

                        default:
                        {
                            printf("Opção inválida.\n");
                            break;
                        }
                    }
                }

                break;
            }

            case 2:
            {
                clear_terminal();
                notify_thread();

                if(_CHECK_FIFO_DATAFLOW() == 1){
                    printf("Fila bloqueada! Desbloqueie em <REGISTRADORES>\n");
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
                            notify_thread();
                            if(ptr_queue == NULL)
                            {
                                init_queue(&ptr_queue);
                            }

                            uint8_t byte;
                            unsigned int temp;

                            printf("Digite o dado: ");
                            scanf("%u", &temp);

                            byte = (uint8_t)temp;
                            add_queue_node(ptr_queue, byte);

                            clear_terminal();
                            notify_thread();
                            break;
                        }

                        case 2:
                        {
                            clear_terminal();
                            remove_queue_node(ptr_queue);
                            notify_thread();
                            break;
                        }

                        case 3:
                        {
                            clear_terminal();
                            notify_thread();
                            if(check_queue(ptr_queue)) break;

                            printf("Inicio da fila: 0x%x", ptr_queue->inicio->data);
                            break;
                        }

                        case 4:
                        {
                            clear_terminal();
                            clear_queue(&ptr_queue);
                            notify_thread();

                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            break;
                        }

                        default:
                        {
                            printf("Opção inválida.\n");
                            break;
                        }
                    }
                }

                break;
            }

            case 3:
            {

                opt = 1;
                while(opt == 1)
                {
                    clear_terminal();

                    int a = menu_reg();
                    switch(a)
                    {
                        case 1:
                        {
                            notify_thread();
                            if(_CHECK_FIFO_DATAFLOW() == 1){
                                _FIFO_UNLOCK_DATAFLOW();    
                            }else{
                                _FIFO_BLOCK_DATAFLOW();
                            }

                            break;
                        }

                        case 2:
                        {
                            notify_thread();
                            if(_CHECK_LIFO_DATAFLOW() == 1){
                                _LIFO_UNLOCK_DATAFLOW();    
                            }else{
                                _LIFO_BLOCK_DATAFLOW();
                            }

                            break;
                        }

                        case 0:
                        {
                            opt = 0;
                            break;
                        }

                        default:
                        {
                            printf("Opção inválida.\n");
                            break;
                        }
                    }
                }

                break;
            }

            case 0:
            {
                printf("Programa encerrado pelo usuário\n");
                clear_stack(&ptr_stack);
                clear_queue(&ptr_queue);
                free(data);
                return;
            }

            default:
            {
                printf("Opção inválida.\n");
                break;
            }
        }
    }
}