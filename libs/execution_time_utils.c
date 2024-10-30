#include <sys/time.h>
#include <stdio.h>
#include "execution_time_utils.h"

void reset_time(struct timeval * var, int n) {
    /* 
        Função para inicializar as variáveis que servem como parâmetros 
        para calcular tempo de execução, recebe como parâmetro um vetor de struct timeval,
        e o tamanho do vetor.
    */
    for (int i = 0; i < n; i++){
        var[i].tv_usec = 2;
        var[i].tv_sec = 2;
    }
}

void reset_total_time(double * total_time, int n) {
    /* 
        Função para inicializar a variável que guarda o tempo total de execução 
        por thread, recebe como parâmetro um vetor de double e o tamanho do vetor
    */
    for (int i = 0; i < n; i++){
        total_time[i] = 0;
    }
}

void compute_execution_time(double * total_time_array, struct timeval * begin, struct timeval * end, int n) {
    for (int t = 0; t < n; t++) {
        total_time_array[t] = (end[t].tv_sec - begin[t].tv_sec) + (end[t].tv_usec - begin[t].tv_usec) / 1000000.0;
    }
}

void show_execution_time_all_threads(double * total_time_per_thread, int n) {
    for (int t = 0; t < n; t++) {
        printf("A thread%d gastou %f segundos. \n", t, total_time_per_thread[t]);
    }
}