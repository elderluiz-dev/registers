# Define o compilador
CC = gcc

# Flags de compilação (Avisos e debug)
CFLAGS = -Wall -Wextra -g

# Diretórios de inclusão (-I) para que o compilador encontre os arquivos .h
INCLUDES = -I./lib/data_queue/include \
           -I./lib/data_stack/include \
           -I./lib/interface/include \
           -I./lib/reg/include

# Lista de todos os arquivos fonte (.c) do projeto
SRCS = main.c \
       lib/data_queue/queue.c \
       lib/data_stack/stack.c \
       lib/interface/interface.c \
       lib/reg/8bit_reg.c

# Transforma a lista de .c em uma lista de arquivos objeto (.o)
OBJS = $(SRCS:.c=.o)

# Nome do arquivo executável final
TARGET = run

# Regra principal
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Regra genérica para compilar cada arquivo .c em um arquivo .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regra para limpar os arquivos compilados (útil para reconstruir o projeto do zero)
clean:
	rm -f $(OBJS) $(TARGET)

# Declara que 'all' e 'clean' não são arquivos
.PHONY: all clean