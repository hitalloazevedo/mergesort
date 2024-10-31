double compute_execution_time(struct timespec begin, struct timespec end);

void show_time_specs(int n_threads, struct timespec begin, struct timespec end, double ** threads_time);