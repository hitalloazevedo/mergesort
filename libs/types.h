#ifndef TYPES_H
#define TYPES_H

typedef struct read_args {
    char ** filenames;
    int n_files;
    int * vector;
    int vector_size;
} t_read_args;

typedef struct sort_args {
    int * array;
    int array_size;
    double execution_time;
} t_sort_args;

#endif