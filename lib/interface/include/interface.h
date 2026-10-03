#pragma once

typedef struct 
{
    int update;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} data_thread;

extern data_thread *data;

int main_menu();
int menu_queue();
int menu_stack();
int menu_reg();

void clear_terminal();

void *interface_reg(void *);
void init_program();
void auto_test();