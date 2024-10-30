#include <stdio.h>
#include <pthread.h>
#include "memory_allocation_utils.h"
#include <string.h>
#include <stdlib.h>
#include "structs_utils.h"
#include "utils.h"

pthread_mutex_t mutex;

void write_output_file(char * output_file, int * content_vector, int content_size){
    FILE * pfile;

    pfile = fopen(output_file, "a");
    char * string = string_allocation(255);

    for (int i = 0; i < content_size; i++){
        sprintf(string, "%d", content_vector[i]);
        strcat(string, "\n");
        fprintf(pfile, string);
    }

    string_deallocation(string);
    fclose(pfile);
}

void * read_input_files(void * args){

    args_t inside_args = *(args_t *) args;
    r_args_t * result = (r_args_t*)malloc(sizeof(r_args_t));

    int * integers_quantity = (int *)malloc(sizeof(int));
    *integers_quantity = 0;
    for (int i = 0; i < inside_args.n_files; i++){
        char * file_path = string_allocation(200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args.filenames[i]);
        *integers_quantity += countFileLines(file_path);
        free(file_path);
    }

    int * numbers_vector = integer_vector_allocation(inside_args.n_files * (*integers_quantity));

    // para cada arquivo atribuido faça

    int j = 0;
    for (int i = 0; i < inside_args.n_files; i++){
        FILE * pfile; // cria um ponteiro para arquivos
        char * file_path = string_allocation(200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args.filenames[i]);

        char * line = string_allocation(255);

        pfile = fopen(file_path, "r");
        string_deallocation(file_path);
        while (fgets(line, 255, pfile) != NULL){
            numbers_vector[j] = atoi(line);
            j++;
        }
        string_deallocation(line);
        fclose(pfile);
    }

    result->vector = numbers_vector;
    result->vector_size = integers_quantity;

    pthread_exit((void *)result);
}