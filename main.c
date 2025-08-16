#include "libs/types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "libs/malloc_utils.h"
#include "libs/io_functions.h"
#include "libs/utils.h"
#include "libs/thread_sort_functions.h"
#include "libs/time_utils.h"
#include <time.h>

int main(int argc, char *argv[]){

    int files_count = argc - 4;
    int threads_count = atoi(argv[1]);
    
    char ** filenames = extract_filenames(argv, argc);
    char * output_filepath = extract_output_filepath(argv, argc);
    
    t_reader_thread_task * tasks = tasks_distributor_for_reader_threads(threads_count, files_count, filenames);

    t_reader_threads_args * thread_args = (t_reader_threads_args *)malloc(sizeof(t_reader_threads_args) * threads_count);
    check_malloc(thread_args, "error to alocate args struct for the thread.");

    
    for (size_t i = 0; i < threads_count; i++){
        thread_args[i].task = &tasks[i];
        thread_args[i].intermediate_array = malloc(sizeof(t_array));
        thread_args[i].intermediate_array->array = NULL;
        thread_args[i].intermediate_array->size = 0;
    }

    execute_reader_threads(threads_count, thread_args);

    t_array * unified_array = merge_intermediate_vectors(thread_args, threads_count);

    t_sort_outcome * sort_result = create_sorted_intermediate_arrays(threads_count, unified_array);

    write_results(output_filepath, threads_count, sort_result);

    show_execution_details(threads_count, sort_result);

    free(unified_array->array);
    free(unified_array);
    dealloc_string_vector(filenames,files_count);
    for (int i = 0; i < threads_count; i++) {
        free(tasks[i].files);
        free(thread_args[i].intermediate_array->array);
        free(thread_args[i].intermediate_array);
        free(sort_result->threads_outcome[i].intermediate_array);
    }
    free(tasks);
    free(thread_args);
    free(sort_result->threads_outcome);
    free(sort_result);
    free(output_filepath);

}