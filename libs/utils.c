#include "utils.h"
#include <string.h>
#include "memory_utils.h"
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

void fill_args_vector(int n_threads, int distribution[], char * filenames[], t_read_args args[]){
    int k = 0, j = 0;
    for (int i = 0; i < n_threads; i++) {
        args[i].filenames = string_vector_allocation(distribution[i], 30);
        args[i].n_files = distribution[i];

        // popula o vetor de argumentos respeitando a distribuição dos arquivos
        // se o vetor de distribuição for [1, 1, 1, 0]
        // Então os argumentos serão
        // args[0].filenames = {"arq1.dat"}
        // args[1].filenames = {"arq1.dat"}
        // args[2].filenames = {"arq1.dat"}
        // args[3].filenames = {}
        while (j < distribution[i]) {
            strcpy(args[i].filenames[j], filenames[k]);
            k++;
            j++;
        }
        j = 0;
    }
}

int countFileLines(char * filename){
    FILE * file;
    file = fopen(filename, "r");
    int c = 0;
    char ch;

    while ((ch = getc(file)) != EOF){
        if (ch == '\n'){ c++; }
    }

    fclose(file);

    return c;
}

void merge_unordened_vectors(int mergedVectorSize, int n_threads, t_read_args * args, int * mergedVector, int * distribution){
    int pos = 0;
    for (int i = 0; i < n_threads; i++){
        if (distribution[i] > 0){
            memcpy(mergedVector + pos, args[i].vector, args[i].vector_size * sizeof(int));
            pos += args[i].vector_size;
        }
    }
}

void merge_pre_ordened_vectors(int mergedVectorSize, int n_threads, t_sort_args * ordened_arrays, int * mergedVector){
    int pos = 0;
    for (int i = 0; i < n_threads; i++){
        memcpy(mergedVector + pos, ordened_arrays[i].array, ordened_arrays[i].array_size * sizeof(int));
        pos += ordened_arrays[i].array_size;
    }   
}