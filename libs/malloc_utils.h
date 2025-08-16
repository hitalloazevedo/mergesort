#ifndef MALLOC_UTILS
#define MALLOC_UTILS

#include <stdlib.h>

char ** malloc_string_vector(int vector_size, int string_size);
void check_malloc(void * ptr, const char * msg);
void dealloc_string_vector(char ** string_vector, size_t size);

#endif