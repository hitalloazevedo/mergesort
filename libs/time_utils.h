#include "types.h"
#include <time.h>

// calcula o tempo de execução, recebendo como parâmetro o momento de inicio e fim
double compute_execution_time(struct timespec begin, struct timespec end);

// Mostra as informações dos tempos de execução
void show_time_specs(int n_threads, struct timespec begin_time, struct timespec end_time, t_sort_args * ordened_vectors);