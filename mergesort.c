#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "libs/memory_allocation_utils.h"
#include "libs/wr_operations.h"
#include "libs/utils.h"

int main(int argc, char *argv[]){

    // Declaração de variáveis e alocação de memória

    int n_files = argc - 4;
    int n_threads = atoi(argv[1]);
    int * distribution = integer_vector_allocation(n_files);
    long int * integers_quantity = (long int *)malloc(sizeof(long int));

    args_t * args = vector_struct_args_allocation(n_threads);

    tasks_distributor(n_files, n_threads, distribution);

    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);

    char ** filenames = string_vector_allocation(n_files, 30);

    // Inicio das operações

    extract_file_names_from_argv(filenames, argv, argc);

    // divisão das tarefas

    printf("threads %d\n", n_threads);
    int k = 0, j = 0;
    for (int i = 0; i < n_threads; i++) {

        printf("thread: %d tarefas: %d\n", i, distribution[i]);

        args[i].filenames = string_vector_allocation(distribution[i], 30);
        args[i].n_files = distribution[i];

        while (j < distribution[i]) {
            strcpy(args[i].filenames[j], filenames[k]);
            k++;
            j++;
        }
        j = 0;
    }


    for (int i = 0; i < n_threads; i++) {
        if (distribution[i] > 0){
            int tstatus = pthread_create(&threads[i], NULL, read, (void *)(&args[i]));
            if (tstatus != 0) {
                printf("Erro ao criar a thread\n");
                exit(EXIT_FAILURE);
            }
        }
    }


    for (int i = 0; i < n_threads; i++) { // para cada thread realizar o join
        if (distribution[i] > 0){
            int rstatus = pthread_join(threads[i], (void **)&integers_quantity); // realiza o join da thread e guarda quantos números a thread leu e escreveu
            if (rstatus) { // se a thread retornar um valor maior que 0, um erro é mostrado
                printf("Erro: pthread_join() returns %d\n", rstatus);
                exit(EXIT_FAILURE);
            }
            
            integers_quantity = (long int *)integers_quantity; // Realiza a conversão do resultado da thread 
            printf("A thread %d leu %ld inteiros\n", i, *integers_quantity);
        }
    }

    // Desalocação de memória
    integer_vector_deallocation(distribution); // desalocando o vetor de inteiros que guarda a distribuição das tarefas
    for (int i = 0; i < n_threads; i++) { // desalocando o vetor de strings dentro da struct args
        string_vector_deallocation(args[i].filenames, args[i].n_files);
    }
    string_vector_deallocation(filenames, 30); // desalocando o vetor de strings que guarda o nome dos arquivos de entrada

    return 0;
}