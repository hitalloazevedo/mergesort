#ifndef THREAD_SORT_FUNCTIONS
#define THREAD_SORT_FUNCTIONS

#include <pthread.h>
#include "types.h"

void * thread_mergesort_executor(void * args);

t_sort_outcome * create_sorted_intermediate_arrays(size_t threads_count, t_array * unified_array);

#endif