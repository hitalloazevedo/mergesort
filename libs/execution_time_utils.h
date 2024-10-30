void reset_time(struct timeval * var, int n);

void reset_total_time(double * total_time, int n);

void compute_execution_time(double * total_time_array, struct timeval * begin, struct timeval * end, int n);

void show_execution_time_all_threads(double * total_time_per_thread, int n);