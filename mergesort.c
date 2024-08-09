#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "execution_time_utils.h"

void * thread_func(void * arg) {
    printf("esta funcionando\n");
}

void * thread_func2(void * arg) {
    for(int c = 0; c < 100000000; c++) {}
    printf("esta funcionando\n");
}

int main() {

    int n_threads = 3; // quantidade de threads

    double * total_time_per_thread = (double *) malloc(sizeof(double) * n_threads); // alocando variável para guardar o tempo de execução total por thread
    struct timeval * inicio = (struct timeval *) malloc(sizeof(struct timeval) * n_threads); // alocando um vetor que servirá de parametro para obter o tempo de execução
    struct timeval * fim = (struct timeval *) malloc(sizeof(struct timeval) * n_threads); // alocando um vetor que servirá de parametro para obter o tempo de execução

    reset_total_time(total_time_per_thread, n_threads); // inicializando tempo total, para garantir que não haverá lixo
    reset_time(inicio, n_threads); // inicializando variáveis de parâmetros, para garantir que não haverá lixo
    reset_time(fim, n_threads); // inicializando variáveis de parâmetros, para garantir que não haverá lixo
 
    pthread_t * threads = malloc(sizeof(pthread_t) * n_threads); // alocando um vetor de threads dinâmicamente
    int * response = (int *) malloc(sizeof(int) * n_threads); // alocando um vetor que irá receber o retorno das threads

    int * arg;

    for (int t = 0; t < n_threads; t++) { // for loop responsável por criar todas as threads
        if (t == 1) {
            response[t] = pthread_create(&threads[t], NULL, thread_func2, arg);
        } else {
            response[t] = pthread_create(&threads[t], NULL, thread_func, arg); // cria uma nova thread, recebe como
        }
    }

    for (int t = 0; t < n_threads; t++) {
        gettimeofday(&inicio[t], NULL); // captura o tempo inicial
        pthread_join(threads[t], NULL); // realiza o join de todas as threads
        gettimeofday(&fim[t], NULL); // captura o tempo final
    }

    compute_execution_time(total_time_per_thread, inicio, fim, n_threads);
    show_execution_time_all_threads(total_time_per_thread, n_threads);

    exit(0);
}