#include <pthread.h>
#include "types.h"

// Conjunto de funções do algoritmo mergesort que foi retirado do github
// Autor: Leandro Gonçalves de Oliveira 
void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);

// Ordena o vetor unificado
void * sortVector(void * args);

// Ordena os vetores intermediários
void sort_intermediate_vectors(pthread_t * threads, int n_threads, int unifiedVectorSize, int * mergedArray, t_sort_args * ordened_vectors,struct timespec * begin_time, struct timespec * end_time);