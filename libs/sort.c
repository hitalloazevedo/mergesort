#define _POSIX_C_SOURCE 199309L
#include "sort.h"
#include <stdlib.h>
#include "types.h"
#include <time.h>
#include <stdio.h>
#include <pthread.h>


// Função que é utilizada pela thread para a ordenção dos vetores intermediários
void * sortVector(void * args){
    // criação das variáveis responsáveis em armazenar os dados do tempo de execução
    struct timespec begin, end;

    // Realiza o cast do argumento da função
    t_sort_args * arg = (t_sort_args *)args;

    // armazena o momento de tempo atual na variável begin
    clock_gettime(CLOCK_MONOTONIC, &begin);
    // chama a função de ordenação mergesort 
    mergesort(arg->array, arg->array_size);
    // armazena o momento de tempo atual na variável end
    clock_gettime(CLOCK_MONOTONIC, &end);

    // calcula os tempo de execução da thread
    arg->execution_time = (end.tv_sec - begin.tv_sec);
    arg->execution_time += (end.tv_nsec - begin.tv_nsec) / 10e9;

    // Finaliza a execução da thread retornando o tempo de execução
    return 0;
}

// ==============================================================================================
// O algoritmo de ordenação abaixo é o mergesort
// Essa algoritmo pode ser encontrado no repositório público do github
// link do repo: https://gist.github.com/olegon/27c2a880c9b932862e60ab5eb89be5b6
// Autor: Leandro Gonçalves de Oliveira 
// ==============================================================================================
/*
  Dado um vetor de inteiros v e um inteiro n >= 0, ordena o vetor v[0..n-1] em ordem crescente.
*/
void mergesort(int *v, int n) {
  int *c = malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(int *v, int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}


/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv] <= c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}

// ==============================================================================================
void sort_intermediate_vectors(pthread_t* threads, int n_threads, int unifiedVectorSize, int * mergedArray, t_sort_args * ordened_vectors,struct timespec * begin_time, struct timespec * end_time){

    // =========================================================================================
    // Definição de variáveis importantes para realizar a divisão do vetor unificado não ordenado
    // Em N vetores intermediários, sendo N == n_threads
    // =========================================================================================
    int segment_size = unifiedVectorSize / n_threads;
    int remainder = unifiedVectorSize % n_threads;
    int start_index = 0;

    clock_gettime(CLOCK_MONOTONIC, begin_time);
    for (int i = 0; i < n_threads; i++){
        // Separa o vetor unificado em n_threads partes iguais, ou o mais balanceado possível
        ordened_vectors[i].array_size = segment_size + (i < remainder ? 1 : 0);
        ordened_vectors[i].array = &mergedArray[start_index];
        start_index += ordened_vectors[i].array_size;
        // Cria uma nova thread passando como parâmetros:
        // A função de ordenação (sortVector) e um vetor para ser ordenado;
        int sort_thread_status = pthread_create(&threads[i], NULL, sortVector, (void *)&ordened_vectors[i]);
        // Verifica se a thread foi instanciada com sucesso
        if (sort_thread_status != 0) {
            perror("Erro ao criar a thread\n");
            exit(EXIT_FAILURE);
        }
        // Aguarda o fim da execução da thread, recebendo um retorno
        // O retorno é um ponteiro de double que aponta para tempo de execução dentro da thread
        int response_sort_thread_status = pthread_join(threads[i], NULL);
        // Verifica se o join foi realizado com êxito
        if (response_sort_thread_status) { 
            printf("Erro: pthread_join() returns %d\n", response_sort_thread_status);
            exit(EXIT_FAILURE);
        }   
    }
    // Guarda o momento de tempo atual na variável end_time
    clock_gettime(CLOCK_MONOTONIC, end_time);
}