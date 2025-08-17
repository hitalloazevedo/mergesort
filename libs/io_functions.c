#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include <limits.h>
#include <time.h>
#include "malloc_utils.h"

void write_results(char * output_filepath, size_t threads_count, t_sort_outcome * sorter_threads_output){
    FILE * fp = fopen(output_filepath, "w+");
    check_malloc(fp, "error to open output file");

    // cria um vetor de tamanho threads_count de indexes que corresponde ao index dos vetores, sendo (index) < (tamanho do vetor)
    int * indexes = calloc(threads_count, sizeof(int));
    check_malloc(indexes, "error allocating indexes array");

    while (1){
        int min_value = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < threads_count; i++){
            // se o index for menor que tamanho do vetor
            if (indexes[i] < sorter_threads_output->threads_outcome[i].intermediate_array->size){
                // o atual recebe o valor do vetor na posição do index
                int current = sorter_threads_output->threads_outcome[i].intermediate_array->array[indexes[i]];
                // comparação para descobrir o menor valor entre os N vetores
                if (current < min_value){
                    min_value = current;
                    min_index = i;
                }
            }
        }

        if (min_index == -1){
            break;
        }

        // Escreve o menor valor no arquivo de saída
        fprintf(fp, "%d\n", min_value);

        indexes[min_index]++;
    }
    
    fclose(fp);
    free(indexes);
}

char ** extract_filenames(char ** argv, int argc){

    size_t file_count = argc - 4;
    if (file_count < 1){
        exit(EXIT_FAILURE);
    }
    char ** filenames = (char **)malloc(file_count * sizeof(char*));

    size_t index = 0;
    for (int i = 0; i < argc; i++){
        if (i > 1 && i < argc - 2){
            filenames[index] = malloc((sizeof(argv[i - 2]) + 1) * sizeof(char));
            strcpy(filenames[index], argv[i]);
            index++;
        }
    }

    return filenames;
}

char * extract_output_filepath(char ** argv, int argc){
    char * output_filepath = malloc(sizeof(char) * 50);
    check_malloc(output_filepath, "error to alocate filepath.");
    strcpy(output_filepath, "output");
    strcat(output_filepath, "/");
    strcat(output_filepath, argv[argc - 1]);
    return output_filepath;
}

void * read_multiple_input_files(void * args) {
    t_reader_threads_args * reader_thread_args = (t_reader_threads_args *) args;

    size_t capacity = 10000;
    size_t count = 0;

    int * data = (int*)malloc(sizeof(int) * capacity);
    check_malloc(data, "error to allocate int vector");

    for (size_t i = 0; i < reader_thread_args->task->count; i++) {
        if (reader_thread_args->task->count == 0) return 0;
        char * file_path = (char*)malloc(sizeof(char) * 200);
        strcpy(file_path, "inputs/");
        strcat(file_path, reader_thread_args->task->files[i]);

        
        FILE * fp = fopen(file_path, "r");
        printf("%s\n", file_path);
        if (fp == NULL){
            fprintf(stderr, "%s '%s': %s\n", "error to alocate memory", file_path, strerror(errno));
            exit(EXIT_FAILURE);
        }
        free(file_path);

        int num;
        while (fscanf(fp, "%d", &num) == 1) {
            if (count == capacity) {
                capacity *= 2;
                int * temp = realloc(data, capacity * sizeof(int));
                check_malloc(temp, "error to reallocate int array");
                data = temp;
            }
            data[count++] = num;
        }

        fclose(fp);
    }

    if (count != capacity) {
        int * temp = realloc(data, count * sizeof(int));
        check_malloc(temp, "error to shrink int array");
        data = temp;
    }

    reader_thread_args->intermediate_array->array = data;
    reader_thread_args->intermediate_array->size = count;

    return 0;
}


void execute_reader_threads(size_t threads_count, t_reader_threads_args * arg){

    pthread_t * threads_array = (pthread_t *) malloc(sizeof(pthread_t) * threads_count);
    check_malloc(threads_array, "error to alocate vector of threads");

    for (size_t i = 0; i < threads_count; i++) {
        if (arg[i].task->count > 0) {
            if (pthread_create(&threads_array[i], NULL, read_multiple_input_files, (void *)(&arg[i])) != 0) {
                perror("Erro ao criar a thread\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Espera todas terminarem
    for (size_t i = 0; i < threads_count; i++) {
        if (arg[i].task->count > 0) {
            int join_status = pthread_join(threads_array[i], NULL);
            if (join_status) {
                fprintf(stderr, "Erro: pthread_join() returns %d\n", join_status);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(threads_array);
}