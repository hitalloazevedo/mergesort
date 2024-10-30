# Nome do executável
EXEC = mergesort

# Diretórios
SRC_DIR = .
LIB_DIR = ./libs

# Arquivos principais
MAIN_SRC = $(SRC_DIR)/mergesort.c

# Busca por todos os arquivos .c na pasta libs
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(LIB_DIR)

# Geração dos objetos correspondentes
OBJS = $(MAIN_SRC:.c=.o) $(LIB_SRCS:.c=.o)

# Compilação
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regras para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(EXEC) $(OBJS)

# Para rodar o programa após compilado
run: $(EXEC)
	./$(EXEC)
