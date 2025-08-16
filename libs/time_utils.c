#include <stdio.h>
#include <time.h>
#include "time_utils.h"

double get_elapsed_time_in_seconds(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9;
}

char* format_time_auto(double seconds) {
    char *buffer = malloc(50);  // espaço suficiente para a string
    if (!buffer) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    if (seconds >= 1.0) {
        sprintf(buffer, "%.6f s", seconds);
    } else if (seconds >= 1e-3) {
        sprintf(buffer, "%.3f ms", seconds * 1e3);
    } else if (seconds >= 1e-6) {
        sprintf(buffer, "%.3f µs", seconds * 1e6);
    } else {
        sprintf(buffer, "%.3f ns", seconds * 1e9);
    }

    return buffer;
}