#include <bits/types/siginfo_t.h>
#include "thread_sort_functions.h"
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "malloc_utils.h"
#include "time_utils.h"
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "mergesort.h"

void * thread_mergesort_executor(void * args){
  struct timespec begin, end;
  t_sorter_threads_args * arg = (t_sorter_threads_args *)args;

  clock_gettime(CLOCK_MONOTONIC, &begin);
  mergesort(arg->intermediate_array->array, arg->intermediate_array->size);
  clock_gettime(CLOCK_MONOTONIC, &end);
  
  arg->execution_time = get_elapsed_time_in_seconds(begin, end);

  return NULL;
}

t_sort_outcome * create_sorted_intermediate_arrays(size_t threads_count, t_array * unified_array){

    // Aloca dinamicamente o array de threads
    pthread_t *threads_array = malloc(sizeof(pthread_t) * threads_count);
    check_malloc(threads_array, "error to alocate threads array.");

    t_sorter_threads_args * args = (t_sorter_threads_args*)malloc(sizeof(t_sorter_threads_args) * threads_count);

    // Divide o array unificado em segmentos balanceados
    size_t segment_size = unified_array->size / threads_count;
    size_t remainder = unified_array->size % threads_count;
    size_t start_index = 0;

    struct timespec begin, end;
    // Marca o início do tempo
    clock_gettime(CLOCK_MONOTONIC, &begin);

    for (size_t i = 0; i < threads_count; i++) {
      args[i].intermediate_array = calloc(1, sizeof(t_array));
      check_malloc(args[i].intermediate_array, "malloc intermediate_array");
      args[i].intermediate_array->size = segment_size + (i < remainder ? 1 : 0);
      args[i].intermediate_array->array = &unified_array->array[start_index];
      start_index += args[i].intermediate_array->size;

        if (pthread_create(
          &threads_array[i], 
          NULL, 
          thread_mergesort_executor,
          (void *)&args[i]) != 0) 
        {
            perror("Erro ao criar thread");
            free(threads_array);
            exit(EXIT_FAILURE);
        }
    }

    for (size_t i = 0; i < threads_count; i++) {
        if (pthread_join(threads_array[i], NULL) != 0) {
            fprintf(stderr, "Erro no pthread_join da thread %zu\n", i);
            free(threads_array);
            exit(EXIT_FAILURE);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    t_sort_outcome * result = malloc(sizeof(t_sort_outcome));
    result->execution_time = get_elapsed_time_in_seconds(begin, end);
    result->threads_outcome = (t_sorter_threads_args*)args;

    free(threads_array);

    return result;
}

// ==============================================================================================