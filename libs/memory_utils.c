#include "memory_utils.h"
#include <stdlib.h>
#include <stdio.h>
// Structs

t_read_args * vector_struct_read_args_allocation(int n_threads){
    t_read_args * args = (t_read_args *) malloc(sizeof(t_read_args) * n_threads);
    if (args == NULL){
        perror("Erro ao alocar vetor de struct\n");
        exit(EXIT_FAILURE);
    }
    return args;
}

t_read_args_return ** pointer_vector_read_args_return_allocation(int n_threads){
    t_read_args_return ** vector = (t_read_args_return **)malloc(sizeof(t_read_args_return*) * n_threads); 
    if (vector == NULL){
        perror("Erro ao alocar vetor de ponteiro de struct\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n_threads; i++){
        vector[i] = (t_read_args_return *)malloc(sizeof(t_read_args_return));
        if (vector[i] == NULL){
            perror("Erro ao alocar ponteiro de struct\n");
            exit(EXIT_FAILURE);
        }
    }

    return vector;
}

//Strings
char * string_allocation(int string_length) {
    char * string = (char *) malloc(sizeof(char) * string_length);
    if (string == NULL){
        perror("Erro ao alocar string\n");
        exit(EXIT_FAILURE);
    }
    return string;
}

char ** string_vector_allocation(int vector_size, int string_length){
    char ** string_vector = (char **) malloc(sizeof(char *) * vector_size);
    if (string_vector == NULL){
        perror("Erro ao alocar vetor de strings\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vector_size; i++){
        string_vector[i] = (char *) malloc(sizeof(char) * string_length);
        if (string_vector[i] == NULL){
            perror("Erro ao alocar string\n");
            exit(EXIT_FAILURE);
        }
    }
    return string_vector;
}

void string_deallocation(char * string){
    free(string);
}

void string_vector_deallocation(char ** string_vector, int vector_size){
    for (int i = 0; i < 1; i++){
        free(string_vector[0]);
    }
    free(string_vector);
}

// Integers

int * integer_vector_allocation(int vector_size){
    int * vector = (int *) malloc(sizeof(int) * vector_size);
    if (vector == NULL){
        perror("Erro ao alocar vetor de inteiros\n");
        exit(EXIT_FAILURE);
    }
    return vector;
}

int ** integer_matrix_allocation(int rows, int columns){
    int ** matrix = (int **) malloc(sizeof(int *) * rows);
    for (int r = 0; r < rows; r++){
        matrix[r] = (int *) malloc(sizeof(int) * columns);
    }
    return matrix;
}

void integer_matrix_deallocation(int ** matrix, int rows){ 
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}


void integer_vector_deallocation(int * vector){
    free(vector);
}

// Double

double ** double_pointer_vector_allocation(int vector_size){
    double ** vector = (double **)malloc(sizeof(double*) * vector_size);
    if (vector == NULL){
        perror("Erro ao alocar matriz de double\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vector_size; i++){
        vector[i] = (double *)malloc(sizeof(double));
        if (vector[i] == NULL){
            perror("Erro ao alocar ponteiro de double\n");
            exit(EXIT_FAILURE);
        }
    }
    return vector;
}

void double_pointer_vector_deallocation(double ** vector, int vector_size){
    for (int i = 0; i < vector_size; i++){
        free(vector[i]);
    }
    free(vector);
}
