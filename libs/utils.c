#include "utils.h"
#include <string.h>
#include "malloc_utils.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "time_utils.h"
#include <string.h>

t_reader_thread_task * tasks_distributor_for_reader_threads(int threads_count, int files_count, char **filenames) {
    // Aloca a lista de tarefas
    t_reader_thread_task *tasks = (t_reader_thread_task*)malloc(threads_count * sizeof(t_reader_thread_task));
    check_malloc(tasks, "error to alocate memory to read tasks.");

    int q = files_count / threads_count; // quantidade base por thread
    int r = files_count % threads_count; // threads que recebem 1 extra

    int file_index = 0; // índice global dos arquivos

    for (int i = 0; i < threads_count; i++) {
        int num_files = (i < r) ? q + 1 : q;

        tasks[i].count = num_files;
        tasks[i].files = malloc(num_files * sizeof(char *));
        check_malloc(tasks[i].files, "error to alocate memory to filenames array.");

        for (int j = 0; j < num_files; j++) {
            tasks[i].files[j] = filenames[file_index++];
        }
    }

    return tasks;
}

t_array * merge_intermediate_vectors(t_reader_threads_args * args, size_t threads_count){
    t_array * result = (t_array *)malloc(sizeof(t_array));
    result->size = 0;
    for (size_t i = 0; i < threads_count; i++) {
        result->size += args[i].intermediate_array->size;
    }

    int * merged = (int *) malloc(sizeof(int) * result->size);
    check_malloc(merged, "error to allocate unifed array");
    
    size_t pos = 0;
    for (size_t i = 0; i < threads_count; i++) {
        t_array *res = args[i].intermediate_array;
        for (size_t j = 0; j < res->size; j++) {
            merged[pos++] = res->array[j];
        }
    }

    result->array = merged;
    return result;
}

void print_array(int * array, size_t size){
    for (size_t i = 0; i < size; i++){
        printf("%d -> ", array[i]);
    }
    printf("\n");
}

void show_execution_details(size_t threads_count, t_sort_outcome * sort_result){
    long long integers_processed = 0;
    for (size_t i = 0; i < threads_count; i++){
        integers_processed += sort_result->threads_outcome[i].intermediate_array->size;
    }
    printf("======== Results =========\n");

    printf("Total of integers processed: ");
    print_with_dots(integers_processed);

    char *group_time_str = format_time_auto(sort_result->execution_time);
    printf("Threads group time (create until join): %s\n", group_time_str);
    free(group_time_str);

    for (size_t i = 0; i < threads_count; i++){
        char *thread_time_str = format_time_auto(sort_result->threads_outcome[i].execution_time);
        printf("  - Thread (%ld) took %s to sort %ld integers.\n", i + 1, thread_time_str, sort_result->threads_outcome[i].intermediate_array->size);
        free(thread_time_str);
    }
}

void print_with_dots(long long n) {
    char buffer[32];
    sprintf(buffer, "%lld", n);

    int len = strlen(buffer);
    int first_group = len % 3;
    if (first_group == 0) first_group = 3;

    for (int i = 0; i < len; i++) {
        if (i != 0 && (i - first_group) % 3 == 0) {
            putchar('.');
        }
        putchar(buffer[i]);
    }
    putchar('\n');
}