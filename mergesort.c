#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "libs/memory_allocation_utils.h"
#include "libs/wr_operations.h"
#include "libs/utils.h"
#include "classification.h"

void * func(void * args){
    r_args_t * arg = (r_args_t *)args;

    mergesort(arg->vector, *arg->vector_size);

    return (void *)NULL;
}

int main(int argc, char *argv[]){

    // Declaração de variáveis e alocação de memória

    int n_files = argc - 4;
    int n_threads = atoi(argv[1]);
    int * distribution = integer_vector_allocation(n_files);

    args_t * args = vector_struct_args_allocation(n_threads);
    // r_args_t * result_vector = (r_args_t*)malloc(sizeof(r_args_t) * n_threads);

    tasks_distributor(n_files, n_threads, distribution);

    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);

    char ** filenames = string_vector_allocation(n_files, 30);

    extract_file_names_from_argv(filenames, argv, argc);

    printf("threads %d\n", n_threads);
    fill_args_vector(n_threads, distribution, filenames, args);


    r_args_t ** preSortedArrays = (r_args_t **)malloc(sizeof(r_args_t*) * n_threads); 


    int sizeMergedArray = 0;
    r_args_t * result = (r_args_t*)malloc(sizeof(r_args_t));
    for (int i = 0; i < n_threads; i++) {
        if (distribution[i] > 0){
            int readThreadStatus = pthread_create(&threads[i], NULL, read_input_files, (void *)(&args[i]));
            if (readThreadStatus != 0) {
                printf("Erro ao criar a thread\n");
                exit(EXIT_FAILURE);
            }


            int responseReadThreadStatus = pthread_join(threads[i], (void **)&result); // realiza o join da thread e guarda quantos números a thread leu e escreveu
            if (responseReadThreadStatus) { // se a thread retornar um valor maior que 0, um erro é mostrado
                printf("Erro: pthread_join() returns %d\n", responseReadThreadStatus);
                exit(EXIT_FAILURE);
            }   

            result = (r_args_t *)result;

            int orderThreadStatus = pthread_create(&threads[i], NULL, func, (void *)(result));
            if (orderThreadStatus != 0) {
                printf("Erro ao criar a thread\n");
                exit(EXIT_FAILURE);
            }
            int responseOrderThreadStatus = pthread_join(threads[i], NULL);
            if (responseOrderThreadStatus) { // se a thread retornar um valor maior que 0, um erro é mostrado
                printf("Erro: pthread_join() returns %d\n", responseOrderThreadStatus);
                exit(EXIT_FAILURE);
            }

            sizeMergedArray += *result->vector_size;

            preSortedArrays[i] = result;
        }
    }

    int * mergedArray = (int *)malloc(sizeof(int) * sizeMergedArray);

    int pos = 0;
    for (int i = 0; i < n_threads; i++){
        if (distribution[i] > 0){
            memcpy(mergedArray + pos, preSortedArrays[i]->vector, *preSortedArrays[i]->vector_size * sizeof(int));
            pos += *preSortedArrays[i]->vector_size;
        }
    }

    mergesort(mergedArray, sizeMergedArray);

    for (int i = 0; i < sizeMergedArray; i++){
        printf("%d\n", mergedArray[i]);
    }

    // Desalocação de memória
    integer_vector_deallocation(distribution); // desalocando o vetor de inteiros que guarda a distribuição das tarefas
    for (int i = 0; i < n_threads; i++) { // desalocando o vetor de strings dentro da struct args
        string_vector_deallocation(args[i].filenames, args[i].n_files);
    }
    string_vector_deallocation(filenames, 30); // desalocando o vetor de strings que guarda o nome dos arquivos de entrada

    return 0;
}