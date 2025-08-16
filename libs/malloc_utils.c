#include "malloc_utils.h"
#include <stdlib.h>
#include <stdio.h>

char ** string_vector_allocation(int vector_size, int string_size){
    char ** array = (char **)malloc(sizeof(char*) * vector_size);
    check_malloc(array, "Erro to alocate memory for string vector");
    
    for (int i = 0; i < vector_size; i++){
        array[i] = (char *)malloc(sizeof(char) * string_size);
        check_malloc(array, "error to alocate memory for string");
    }
    return array;
}

void dealloc_string_vector(char ** string_vector, size_t size){
    for (size_t i = 0; i < size; i++){
        free(string_vector[i]);
    }
    free(string_vector);
}

void check_malloc(void * ptr, const char * msg){
    if (ptr == NULL){
        fprintf(stderr, "Erro ao alocar memória %s\n", msg);
        exit(EXIT_FAILURE);
    }
}
