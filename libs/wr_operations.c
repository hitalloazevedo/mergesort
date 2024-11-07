#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include <limits.h>
#include <time.h>

void write_output_file(char * output_file, int n_threads, t_sort_args * ordened_vectors){
    FILE * pfile;

    pfile = fopen(output_file, "w+");
    if (pfile == NULL){
        printf("erro: erro ao abrir o arquivo de saída\n");
        exit(EXIT_FAILURE);
    }

    // cria um vetor de tamanho n_threads de indexes que corresponde ao index dos vetores, sendo (index) < (tamanho do vetor)
    int indexes[n_threads];
    for (int i = 0; i < n_threads; i++){
        indexes[i] = 0;
    }

    while (1){
        int min_value = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < n_threads; i++){
            // se o index for menor que tamanho do vetor
            if (indexes[i] < ordened_vectors[i].array_size){
                // o atual recebe o valor do vetor na posição do index
                int current = ordened_vectors[i].array[indexes[i]];
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
        fprintf(pfile, "%d\n", min_value);

        indexes[min_index]++;
    }
    
    fclose(pfile);
}

void * read_input_files(void * args){

    t_read_args * inside_args = (t_read_args *) args;

    int integers_quantity = 0;

    // Conta a quantidade de linhas no arquivo
    for (int i = 0; i < inside_args->n_files; i++){
        char * file_path = (char *)malloc(sizeof(char) * 200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args->filenames[i]);
        integers_quantity += countFileLines(file_path);
        free(file_path);
    }

    inside_args->vector = (int *)malloc(sizeof(int) * integers_quantity);
    inside_args->vector_size = integers_quantity;

    // Realiza a leitura e armazena no vetor de resultado
    int j = 0;
    for (int i = 0; i < inside_args->n_files; i++){
        FILE * pfile; // cria um ponteiro para arquivos
        char * file_path = (char *)malloc(sizeof(char) * 200);
        strcpy(file_path, "inputs/");
        strcat(file_path, inside_args->filenames[i]);

        char * line = (char *)malloc(sizeof(char) * 20);

        pfile = fopen(file_path, "r");
        if (pfile == NULL){
            printf("erro: erro ao abrir o arquivo para leitura\n");
            exit(EXIT_FAILURE);
        }
        
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