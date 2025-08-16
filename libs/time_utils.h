#include "types.h"
#include <time.h>

double get_elapsed_time_in_seconds(struct timespec begin, struct timespec end);
char* format_time_auto(double seconds);