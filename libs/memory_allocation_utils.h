#include "structs_utils.h"

args_t * struct_args_allocation(int n_args);

// Strings
char * string_allocation(int string_length);

char ** string_vector_allocation(int vector_size, int string_length);

void string_deallocation(char * string);

void string_vector_deallocation(char ** string_vector, int vector_size);

// Integers
int * integer_vector_allocation(int vector_size);

int ** integer_matrix_allocation(int rows, int columns);

void integer_matrix_deallocation(int ** matrix, int rows);

void integer_vector_deallocation(int * vector);
