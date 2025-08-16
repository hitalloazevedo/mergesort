#include <pthread.h>
#include <time.h>
#include "types.h"

// Escreve o vetor no arquivo de saída
void write_results(char * output_filepath, size_t threads_count, t_sort_outcome * sorter_threads_output);

// Realiza a leitura dos arquivos de entrada, função de argumento da trhead
void * read_multiple_input_files(void * args);

// Procedimento responsável pela criação do conjunto das threads de leitura
void execute_reader_threads(size_t threads_count, t_reader_threads_args * args);

char ** extract_filenames(char ** argv, int argc);
char * extract_output_filepath(char ** argv, int argc);