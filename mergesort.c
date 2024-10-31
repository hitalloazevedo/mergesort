#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "memory_utils.h"
#include "wr_operations.h"
#include "utils.h"
#include "sort.h"
#include "time_utils.h"
#include <time.h>

int main(int argc, char *argv[]){

    // =========================================================================================
    // Criação das variáveis que irão armazenar a quantidade de arquivos e a quantidade de threads
    int n_files = argc - 4;
    int n_threads = atoi(argv[1]);
    // =========================================================================================



    // =========================================================================================
    // Aloca um vetor de distribuição de quantos arquivos cada thread irá ler
    int * distribution = integer_vector_allocation(n_threads);
    // Popula o vetor de distribuição
    tasks_distributor(n_files, n_threads, distribution);
    // =========================================================================================



    // =========================================================================================
    // Aloca um vetor de strings que armazenará os nomes dos arquivos de entrada 
    char ** filenames = string_vector_allocation(n_files, 30);
    // Extrai do vetor argumentos (argv) os nomes dos arquivos de entrada
    extract_file_names_from_argv(filenames, argv, argc);
    // =========================================================================================



    // =========================================================================================
    // Alocação dos vetores que são utilizados para passar parâmetros para as threads
    // =========================================================================================
    // aloca o vetor de struct que será utilizado como argumento para as threads de leitura
    t_read_args * args = vector_struct_read_args_allocation(n_threads);
    // Popula o vetor de struct de argumentos para as threads de leitura
    fill_args_vector(n_threads, distribution, filenames, args);

    // aloca o vetor de struct que recebe os inteiros lidos nas threads 
    // posteriormente, ele é utilizado para realizar a unificação não ordenada um um único vetor
    t_read_args_return ** unordered_vectors = pointer_vector_read_args_return_allocation(n_threads);

    // aloca o vetor de struct que armazena os vetores intemediários já ordenados
    // posteriormente é utilizado para realizar a unificação ordenada um um único vetor
    t_sort_args * ordened_vectors = (t_sort_args *)malloc(sizeof(t_sort_args) * n_threads); 

    // aloca uma struct que recebe o resultado de cada thread de leitura (vetores não ordenados), 
    // os seus dados são armazenados em um vetor de struct que será utilizado para alimentar
    // as threads de ordenação
    t_read_args_return * result = (t_read_args_return*)malloc(sizeof(t_read_args_return));
    // =========================================================================================



    // =========================================================================================
    // Criação da variável que irá armazenar o tamanho dos vetores unificados, o que também
    // corresponde a quantidade total de inteiros que o programa irá processar
    int unifiedVectorSize = 0;
    // =========================================================================================

    // =========================================================================================
    // Aloca o vetor de threads que o programa irá utilizar
    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);
    // =========================================================================================



    // =========================================================================================
    // Etapa de leitura dos arquivos de entrada
    // =========================================================================================
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
            int response_read_thread_status = pthread_join(threads[i], (void **)&result); 
            // verifica se o join foi realizado com êxito
            if (response_read_thread_status) { 
                printf("Erro: pthread_join() returns %d\n", response_read_thread_status);
                exit(EXIT_FAILURE);
            }   

            // Realiza o cast do ponteiro de resultados
            result = (t_read_args_return *)result;
            // Incrementa o tamanho do vetor unificado com os tamanhos dos vetores intermediários
            unifiedVectorSize += *result->array_size;
            // Popula o vetor de struct de argumentos que será utilizado pelas threads de ordenação
            unordered_vectors[i] = result;
        }
    }
    // Desaloca o vetor de nomes de arquivo
    string_vector_deallocation(filenames, 30);
    // =========================================================================================


    
    // =========================================================================================
    // Unificando os vetores não ordenados resultantes da leitura em um único vetor não ordenado
    // =========================================================================================
    // Aloca memória do vetor não ordenado
    int * mergedArray = integer_vector_allocation(unifiedVectorSize);
    // Realiza o merge no vetor
    merge_unordened_vectors(unifiedVectorSize, n_threads, unordered_vectors, mergedArray, distribution);
    // Desaloca memória do vetor de distribuição, não é mais utilizado daqui para frente
    integer_vector_deallocation(distribution);
    // =========================================================================================



    // =========================================================================================
    // Definição de variáveis importantes para realizar a divisão do vetor unificado não ordenado
    // Em N vetores intermediários, sendo N == n_threads
    // =========================================================================================
    int segment_size = unifiedVectorSize / n_threads;
    int remainder = unifiedVectorSize % n_threads;
    int start_index = 0;
    // =========================================================================================



    // =========================================================================================
    // Etapa de ordenação dos vetores intermediários
    // =========================================================================================
    // Aloca memória e instancia variáveis para armazenar dados dos tempos de execução
    struct timespec begin_time, end_time;
    double ** threads_processing_time = double_pointer_vector_allocation(n_threads);

    // Guarda o momento de tempo atual na variável begin_time
    clock_gettime(CLOCK_MONOTONIC, &begin_time);
    for (int i = 0; i < n_threads; i++){
        // Separa o vetor unificado em n_threads partes iguais, ou o mais balanceado possível
        ordened_vectors[i].array_size = segment_size + (i < remainder ? 1 : 0);
        ordened_vectors[i].array = (int *)malloc(sizeof(int) * ordened_vectors[i].array_size);
        ordened_vectors[i].array = &mergedArray[start_index];
        start_index += ordened_vectors[i].array_size;

        // Cria uma nova thread passando como parâmetros:
        // A função de ordenação (sortVector) e um vetor para ser ordenado;
        int sort_thread_status = pthread_create(&threads[i], NULL, sortVector, (void *)&ordened_vectors[i]);
        // Verifica se a thread foi instanciada com sucesso
        if (sort_thread_status != 0) {
            perror("Erro ao criar a thread\n");
            exit(EXIT_FAILURE);
        }

        // Aguarda o fim da execução da thread, recebendo um retorno
        // O retorno é um ponteiro de double que aponta para tempo de execução dentro da thread
        int response_sort_thread_status = pthread_join(threads[i], (void**)&threads_processing_time[i]);
        // Verifica se o join foi realizado com êxito
        if (response_sort_thread_status) { 
            printf("Erro: pthread_join() returns %d\n", response_sort_thread_status);
            exit(EXIT_FAILURE);
        }   

        // Converte cada ponteiro de (void**) para seu tipo especifico (double *) 
        threads_processing_time[i] = (double *)threads_processing_time[i];
    }
    // Guarda o momento de tempo atual na variável end_time
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    // =========================================================================================



    // =========================================================================================
    // Etapa de ordenação do vetor unificado
    // =========================================================================================

    // Aloca um vetor de inteiros que será utilizado para armazenar todos 
    // os inteiros ordenados
    int * mergedOrdenedArray = integer_vector_allocation(unifiedVectorSize);

    // Realiza um merge dos vetores pré ordenados em um único vetor
    merge_pre_ordened_vectors(unifiedVectorSize, n_threads, ordened_vectors, mergedOrdenedArray);

    // Realiza a ordenação do vetor unificado
    mergesort(mergedOrdenedArray, unifiedVectorSize);
    // =========================================================================================



    // =========================================================================================
    // Realiza a escrita dos resultados no arquivo de saida
    write_output_file("outputs/saida.dat", mergedOrdenedArray, unifiedVectorSize);
    // =========================================================================================



    // =========================================================================================
    // Desaloca os vetores unificados (ordenado e não ordenado)
    integer_vector_deallocation(mergedArray);
    integer_vector_deallocation(mergedOrdenedArray);
    // =========================================================================================



    // =========================================================================================
    // Imprime no terminal todas as informações sobres os tempos de execução
    show_time_specs(n_threads, begin_time, end_time, threads_processing_time);
    // =========================================================================================



    // =========================================================================================
    // Desaloca o vetor que armazena os tempos de execução de cada thread
    double_pointer_vector_deallocation(threads_processing_time, n_threads);
    // =========================================================================================



    // =========================================================================================
    // Desaloca o vetor struct de argumentos da memória 
    for (int i = 0; i < n_threads; i++) { 
        string_vector_deallocation(args[i].filenames, args[i].n_files);
    }
    free(args);

    // Outras desalocações de memória
    for (int i = 0; i < n_threads; i++){
        free(unordered_vectors[i]->array);
    }
    free(unordered_vectors);
    free(ordened_vectors);
    free(result);
    free(threads);
    // =========================================================================================

    return 0;
}