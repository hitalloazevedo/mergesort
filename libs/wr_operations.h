#include <pthread.h>
#include <time.h>
#include "types.h"

// Escreve o vetor no arquivo de saída
void write_output_file(char * output_file, int * content_vector, int content_size);

// Realiza a leitura dos arquivos de entrada, função de argumento da trhead
void * read_input_files(void * args);

// Procedimento responsável pela criação do conjunto das threads de leitura
void handle_read_files(pthread_t * threads, int n_threads, int * distribution, int * unifiedVectorSize, t_read_args * args);