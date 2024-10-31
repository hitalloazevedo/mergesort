#include "types.h"

// Structs

// aloca um vetor de struct args de tamanho N
// int n_threads: Quantidade de struct args no vetor
t_read_args * vector_struct_read_args_allocation(int n_threads);

// aloca um vetor de ponteiros de struct de tamanho N
// int n_threads: Quantidade de ponteiros de struct args retorno no vetor
t_read_args_return ** pointer_vector_read_args_return_allocation(int n_threads);

// Strings

// aloca uma string de tamanho N
// int string_length: tamanho da string
char * string_allocation(int string_length);

// Aloca um vetor de strings
// int vector_size: Tamanho do vetor
// int string_length: Tamanho das strings
char ** string_vector_allocation(int vector_size, int string_length);

// Desaloca uma string
// char * string: endereço de memória da string
void string_deallocation(char * string);

// Desaloca um vetor de strings
// char ** string_vector: endereço da matriz de caracteres
// int vector_size: número de linhas da matriz
void string_vector_deallocation(char ** string_vector, int vector_size);

// Integers

// Aloca um vetor de inteiros de tamanho N
// int vector_size: quantidades de inteiros no vetor
int * integer_vector_allocation(int vector_size);

// Aloca uma matriz de inteiros
// int rows: quantidade de linhas da matriz
// int columns: quantidade de colunas da matriz (tamanho do vetor de inteiro)
int ** integer_matrix_allocation(int rows, int columns);

// Desaloca uma matriz de inteiros
// int ** matrix: endereço de memória da matriz
// int rows: quantidade de linhas da matriz
void integer_matrix_deallocation(int ** matrix, int rows);

// Desaloca um vetor de inteiros
// int * vector: endereço de memória do vetor
void integer_vector_deallocation(int * vector);

double ** double_pointer_vector_allocation(int vector_size);

void double_pointer_vector_deallocation(double ** vector, int vector_size);
