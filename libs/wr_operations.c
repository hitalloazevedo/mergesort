#include <stdio.h>
#include <pthread.h>
#include "memory_allocation_utils.h"
#include <string.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void write(char * output_file, int * content_vector, int content_size){
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

void * read(void * args){
    args_t inside_args = *(args_t *) args;

    long int * integers_quantity = (long int *)malloc(sizeof(long int));
    *integers_quantity = (long int)0;

    // aloca uma matriz de tamanho linhas == N arquivos, e colunas até 1000 inteiros
    int ** all_numbers = integer_matrix_allocation(inside_args.n_files, 100000);

    // para cada arquivo atribuido faça
    for (int i = 0; i < inside_args.n_files; i++){
        FILE * pfile; // cria um ponteiro para arquivos

        char * file_path = string_allocation(200);

        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args.filenames[i]);

        char * line = string_allocation(255);

        pfile = fopen(file_path, "r");
        string_deallocation(file_path);
        int rows = 0;
        while (fgets(line, 255, pfile) != NULL){
            // printf("%d\n", atoi(line));
            all_numbers[i][rows] = atoi(line);
            rows++;
            *integers_quantity = *integers_quantity + (long int)1;
        }

        string_deallocation(line);

        fclose(pfile);
        pthread_mutex_lock(&mutex);
        write("outputs/saida.dat", all_numbers[i], rows);
        pthread_mutex_unlock(&mutex);
    }

    integer_matrix_deallocation(all_numbers, inside_args.n_files);

    pthread_exit((void *)integers_quantity);
}