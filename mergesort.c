#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "libs/memory_utils.h"
#include "libs/wr_operations.h"
#include "libs/utils.h"
#include "libs/sort.h"
#include "libs/time_utils.h"
#include <time.h>

int main(int argc, char *argv[]){
    // Criação das variáveis que irão armazenar a quantidade de arquivos e a quantidade de threads
    int n_files = argc - 4;
    int n_threads = atoi(argv[1]);

    // Aloca um vetor de distribuição de quantos arquivos cada thread irá ler
    int * distribution = (int*)malloc(sizeof(int) * n_threads);
    // Popula o vetor de distribuição
    tasks_distributor(n_files, n_threads, distribution);

    // Aloca um vetor de strings que armazenará os nomes dos arquivos de entrada 
    char ** filenames = string_vector_allocation(n_files, 30);
    // Extrai do vetor argumentos (argv) os nomes dos arquivos de entrada
    extract_file_names_from_argv(filenames, argv, argc);

    // aloca o vetor de struct que será utilizado como argumento para as threads de leitura
    t_read_args * args = (t_read_args *)malloc(sizeof(t_read_args) * n_threads);
    // Popula o vetor de struct de argumentos para as threads de leitura
    fill_args_vector(n_threads, distribution, filenames, args);

    // Criação da variável que irá armazenar o tamanho dos vetores unificados, o que também
    // corresponde a quantidade total de inteiros que o programa irá processar
    int unifiedVectorSize = 0;

    // Aloca o vetor de threads que o programa irá utilizar
    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);

    // Realiza a leitura dos arquivos de entradas e gera os vetores como resultado
    handle_read_files(threads, n_threads, distribution, &unifiedVectorSize, args);
    // Desaloca o vetor de nomes de arquivo

    // Aloca um vetor que irá armazenar os inteiros não ordenados
    int * mergedArray = (int*)malloc(sizeof(int) * unifiedVectorSize);
    // Unificando os vetores não ordenados resultantes da leitura em um único vetor não ordenado
    merge_vectors(unifiedVectorSize, n_threads, args, mergedArray, distribution);

    // Aloca memória e instancia variáveis para armazenar dados dos tempos de execução
    struct timespec begin_time, end_time;
    // alocação do vetor de structs intermediário que armazenará os inteiros ordenados
    t_sort_args * ordened_vectors = (t_sort_args *) malloc(sizeof(t_sort_args) * n_threads);
    // Ordenação dos vetores intermediarios
    sort_intermediate_vectors(threads, n_threads, unifiedVectorSize, mergedArray, ordened_vectors, &begin_time, &end_time);

    // Escreve os vetores ordenados no arquivo de saida
    char * output_path = (char *)malloc(sizeof(char) * 30);
    strcpy(output_path, "outputs/");
    strcat(output_path, argv[argc - 1]);
    write_output_file(output_path, n_threads, ordened_vectors);

    // Imprime no terminal todas as informações sobres os tempos de execução
    show_time_specs(n_threads, begin_time, end_time, ordened_vectors);

    // Desalocação de memória
    for (int i = 0; i < n_threads; i++) { 
        for (int k = 0; k < args[i].n_files; k++){
            free(args[i].filenames[k]);
        }
        free(args[i].filenames);
        free(args[i].vector);
    }
    free(args);
    for (int i = 0; i < n_files; i++){
        free(filenames[i]);
    }
    free(output_path);
    free(filenames);
    free(threads);
    free(distribution);
    free(ordened_vectors);
    free(mergedArray);
    return 0;
}