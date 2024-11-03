#include "types.h"
#include <time.h>

double compute_execution_time(struct timespec begin, struct timespec end);

void show_time_specs(int n_threads, struct timespec begin_time, struct timespec end_time, t_sort_args * ordened_vectors);