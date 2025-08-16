#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <time.h>

typedef struct {
    int count;
    char **files; 
} t_reader_thread_task;

typedef struct array {
    int * array;
    size_t size;
} t_array;

typedef struct reader_thread_args {
    t_reader_thread_task * task;
    t_array * intermediate_array;
} t_reader_threads_args;

typedef struct sorter_thread_args {
    t_array * intermediate_array;
    double execution_time;
} t_sorter_threads_args;

typedef struct sort_outcome {
    t_sorter_threads_args * threads_outcome;
    double execution_time;
} t_sort_outcome;

#endif