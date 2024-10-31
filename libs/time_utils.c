#include <time.h>
#include <stdio.h>
#include "time_utils.h"

double compute_execution_time(struct timespec begin_time, struct timespec end_time) {
    double totalExecutionTime;
    totalExecutionTime = (end_time.tv_sec - begin_time.tv_sec);
    totalExecutionTime += (end_time.tv_nsec - begin_time.tv_nsec) / 10e9;
    return totalExecutionTime;
}

void show_time_specs(int n_threads, struct timespec begin_time, struct timespec end_time, double ** threads_processing_time) {
    for (int i = 0; i < n_threads; i++){
        printf("Tempo de execução do Thread %d: %lf segundos.\n", i, *threads_processing_time[i]);
    }
    printf("Tempo total de execução: %lf segundos.\n", compute_execution_time(begin_time, end_time));
}