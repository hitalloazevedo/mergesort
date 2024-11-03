#include <pthread.h>
#include "types.h"

void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);
void * sortVector(void * args);
void sort_intermediate_vectors(pthread_t* threads, int n_threads, int unifiedVectorSize, int * mergedArray, t_sort_args * ordened_vectors,struct timespec * begin_time, struct timespec * end_time);