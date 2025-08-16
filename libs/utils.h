#include "types.h"
#include <stdlib.h>

// Para T threads e A arquivos, retorna um vetor com a distribuição das tarefas
// int tasks: quantidade total de arquivos a serem lidos
// int executors: quantidade de threads disponibilizadas
// int distribution[]: vetor de inteiros que armazenará a distribuição
// Exemplo: T=4 A=3 distribution=[1, 1, 1, 0]
// Exemplo: T=4 A=5 distribution=[2, 1, 1, 1]
t_reader_thread_task * tasks_distributor_for_reader_threads(int threads_count, int files_count, char **filenames);

// Extrai apenas os nomes dos arquivos de entradas da lista de argumentos
// E guarda no vetor de strings filenames
// char ** filenames: Vetor de strings onde será guardado o nome dos arquivos
// char ** argv: Vetor de strings com os argumentos do programa
// int argc: quantidade de argumentos do vetor argv


// Imprime um vetor no terminal
void print_with_dots(long long n);
void print_array(int * array, size_t size);

// Realiza o merge dos vetores não ordenados que são gerados após a leitura dos arquivos
t_array * merge_intermediate_vectors(t_reader_threads_args * args, size_t threads_count);
void show_execution_details(size_t threads_count, t_sort_outcome * sort_result);