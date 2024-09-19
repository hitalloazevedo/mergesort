#include "memory_allocation_utils.h"
#include <stdlib.h>
#include <stdio.h>
// Structs

args_t * vector_struct_args_allocation(int n_args){
    args_t * args = (args_t *) malloc(sizeof(args_t) * n_args);
    return args;
}

//Strings

char * string_allocation(int string_length) {
    char * string = (char *) malloc(sizeof(char) * string_length);
    if (string == NULL){
        printf("não foi possivel alocar a string\n");
        return 0;
    }
    return string;
}

char ** string_vector_allocation(int vector_size, int string_length){
    char ** string_vector = (char **) malloc(sizeof(char *) * vector_size);
    if (string_vector == NULL){
        printf("não foi possivel alocar o vetor de strings\n");
        return 0;
    }
    for (int i = 0; i < vector_size; i++){
        string_vector[i] = (char *) malloc(sizeof(char) * string_length);
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
