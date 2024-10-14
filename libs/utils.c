#include "utils.h"
#include <string.h>
#include "memory_allocation_utils.h"
#include <stdio.h>

void tasks_distributor(int tasks, int executors, int distribution[]) {
    int q = tasks / executors;  // Calcula o quociente
    int r = tasks % executors;  // Calcula o resto

    // Distribui as tarefas
    for (int i = 0; i < executors; i++) {
        if (i < r) {
            distribution[i] = q + 1;  // Os primeiros 'r' executores recebem uma tarefa extra
        } else {
            distribution[i] = q;  // Os restantes recebem 'q' tarefas
        }
    }
}

void extract_file_names_from_argv(char ** filesnames, char ** argv, int argc){
    for (int i = 0; i < argc; i++){
        if (i > 1 && i < argc - 2){
            strcpy(filesnames[i - 2], argv[i]);
        }
    }
}

void fill_args_vector(int n_threads, int distribution[], char * filenames[], args_t args[]){
    int k = 0, j = 0;
    for (int i = 0; i < n_threads; i++) {
        args[i].filenames = string_vector_allocation(distribution[i], 30);
        args[i].n_files = distribution[i];

        while (j < distribution[i]) {
            strcpy(args[i].filenames[j], filenames[k]);
            k++;
            j++;
        }
        j = 0;
    }
}