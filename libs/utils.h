#include "types.h"

// Para T threads e A arquivos, retorna um vetor com a distribuição das tarefas
// int tasks: quantidade total de arquivos a serem lidos
// int executors: quantidade de threads disponibilizadas
// int distribution[]: vetor de inteiros que armazenará a distribuição
// Exemplo: T=4 A=3 distribution=[1, 1, 1, 0]
// Exemplo: T=4 A=5 distribution=[2, 1, 1, 1]
void tasks_distributor(int tasks, int executors, int distribution[]);

// Extrai apenas os nomes dos arquivos de entradas da lista de argumentos
// E guarda no vetor de strings filenames
// char ** filenames: Vetor de strings onde será guardado o nome dos arquivos
// char ** argv: Vetor de strings com os argumentos do programa
// int argc: quantidade de argumentos do vetor argv
void extract_file_names_from_argv(char ** filenames, char ** argv, int argc);

// Preenche o vetor de argumentos que será utilizando dentro da thread com os
// nomes dos arquivos que cada thread irá ler
void fill_args_vector(int n_threads, int distribution[], char * filenames[], t_read_args args[]);

// Imprime um vetor no terminal
void showVector(int * vet, int size);

// Retorna o número de linhas que um arquivo tem
int countFileLines(char * filename);

// Realiza o merge dos vetores não ordenados que são gerados após a leitura dos arquivos
void merge_unordened_vectors(int mergedVectorSize, int n_threads, t_read_args * args, int * mergedVector, int * distribution);

// Realiza o merge dos vetores pré ordenados em um único vetor pré ordenado
void merge_pre_ordened_vectors(int mergedVectorSize, int n_threads, t_sort_args * ordened_arrays, int * mergedVector);