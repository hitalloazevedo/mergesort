#include "memory_utils.h"
#include <stdlib.h>
#include <stdio.h>

char ** string_vector_allocation(int vector_size, int string_size){
    char ** string_vector = (char **)malloc(sizeof(char*) * vector_size);
    if (string_vector == NULL){
        printf("Erro ao alocar vetor de strings\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vector_size; i++){
        string_vector[i] = (char *)malloc(sizeof(char) * string_size);
        if (string_vector[i] == NULL){
            printf("Erro ao alocar string\n");
            exit(EXIT_FAILURE);
        }
    }
    return string_vector;
}