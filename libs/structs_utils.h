#ifndef STRUCT_UTILS_H
#define STRUCT_UTILS_H

typedef struct struct_args {
    char ** filenames;
    int n_files;
} args_t;
typedef struct args_return {
    int * vector_size;
    int * vector;
} r_args_t;

#endif