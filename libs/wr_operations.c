#include <stdio.h>
#include <pthread.h>
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

    t_read_args * inside_args = (t_read_args *) args;

    int integers_quantity = 0;
    for (int i = 0; i < inside_args->n_files; i++){
        char * file_path = (char *)malloc(sizeof(char) * 200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args->filenames[i]);
        integers_quantity += countFileLines(file_path);
        free(file_path);
    }

    inside_args->vector = (int *)malloc(sizeof(int) * integers_quantity);
    inside_args->vector_size = integers_quantity;

    // para cada arquivo atribuido faça

    int j = 0;
    for (int i = 0; i < inside_args->n_files; i++){
        FILE * pfile; // cria um ponteiro para arquivos
        char * file_path = (char *)malloc(sizeof(char) * 200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args->filenames[i]);

        char * line = (char *)malloc(sizeof(char) * 20);

        pfile = fopen(file_path, "r");
        free(file_path);
        while (fgets(line, 20, pfile) != NULL){
            inside_args->vector[j] = atoi(line);
            j++;
        }
        free(line);
        fclose(pfile);
    }

    return 0;
}

void handle_read_files(pthread_t * threads, int n_threads, int * distribution, int * unifiedVectorSize, t_read_args * args){
    for (int i = 0; i < n_threads; i++) {
        // Seguindo a distruição de arquivos para threads
        if (distribution[i] > 0){
            // Cria uma thread passando como parâmetro a função de leitura dos arquivos e uma struct de argumentos
            // A struct contém um vetor com os nomes dos arquivos que serão lidos e a quantidade de arquivos do vetor
            int read_thread_status = pthread_create(&threads[i], NULL, read_input_files, (void *)(&args[i]));
            // verifica se a thread foi criada com sucesso
            if (read_thread_status != 0) {
                perror("Erro ao criar a thread\n");
                exit(EXIT_FAILURE);
            }
            // aguarda a finalização da execução das threads
            int response_read_thread_status = pthread_join(threads[i], NULL); 
            // verifica se o join foi realizado com êxito
            if (response_read_thread_status) { 
                printf("Erro: pthread_join() returns %d\n", response_read_thread_status);
                exit(EXIT_FAILURE);
            }  
            // Incrementa o tamanho do vetor unificado com os tamanhos dos vetores intermediários
            *unifiedVectorSize += args[i].vector_size;
        }
    }
}