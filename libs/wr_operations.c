#include <stdio.h>
#include <pthread.h>
#include "memory_utils.h"
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

void write_output_file(char * output_file, int * content_vector, int content_size){
    FILE * pfile;

    pfile = fopen(output_file, "w+");

    for (int i = 0; i < content_size; i++){
        fprintf(pfile, "%d\n", content_vector[i]);
    }
    
    fclose(pfile);
}

void * read_input_files(void * args){

    t_read_args inside_args = *(t_read_args *) args;
    t_read_args_return * result = (t_read_args_return*)malloc(sizeof(t_read_args_return));

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

    result->array = numbers_vector;
    result->array_size = integers_quantity;

    pthread_exit((void *)result);
}