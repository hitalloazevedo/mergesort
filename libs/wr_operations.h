#include <pthread.h>
#include <time.h>
#include "types.h"

void write_output_file(char * output_file, int * content_vector, int content_size);

void * read_input_files(void * args);

void handle_read_files(pthread_t * threads, int n_threads, int * distribution, int * unifiedVectorSize, t_read_args * args);