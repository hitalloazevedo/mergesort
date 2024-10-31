#ifndef TYPES_H
#define TYPES_H

typedef struct read_args {
    char ** filenames;
    int n_files;
} t_read_args;

typedef struct read_args_return {
    int * array_size;
    int * array;
} t_read_args_return;

typedef struct sort_args {
    int * array;
    int array_size;
} t_sort_args;

#endif