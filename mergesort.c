#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "libs/memory_allocation_utils.h"
#include "libs/wr_operations.h"
#include "libs/utils.h"

int main(int argc, char *argv[]){
    int n_files = argc - 4;
    int n_threads = atoi(argv[1]);
    int * distribution = integer_vector_allocation(n_files);

    args_t * args = struct_args_allocation(n_threads);

    tasks_distributor(n_files, n_threads, distribution);

    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);

    char ** filesnames = string_vector_allocation(n_files, 30);

    for (int i = 0; i < argc; i++){
        if (i > 1 && i < argc - 2){
            strcpy(filesnames[i - 2], argv[i]);
        }
    }

    // divisão das tarefas

    printf("threads %d\n", n_threads);
    int k = 0, j = 0;
    for (int i = 0; i < n_threads; i++) {

        printf("thread: %d tarefas: %d\n", i, distribution[i]);

        args[i].filesnames = string_vector_allocation(distribution[i], 30);
        args[i].n_files = distribution[i];

        while (j < distribution[i]) {
            strcpy(args[i].filesnames[j], filesnames[k]);
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


    for (int i = 0; i < n_threads; i++) {
        if (distribution[i] > 0){
            int rstatus = pthread_join(threads[i], NULL);
            if (rstatus) {
                printf("Erro: pthread_join() returns %d\n", rstatus);
                exit(EXIT_FAILURE);
            }
        }
    }

    integer_vector_deallocation(distribution);
    for (int i = 0; i < n_threads; i++) {
        string_vector_deallocation(args[i].filesnames, args[i].n_files);
    }
    // free(args);
    string_vector_deallocation(filesnames, 30);

    return 0;
}