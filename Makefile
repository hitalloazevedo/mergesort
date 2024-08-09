CC=gcc

program: mergesort.o execution_time_utils.o
	$(CC) mergesort.o execution_time_utils.o -o program

mergesort.o: mergesort.c execution_time_utils.o 
	$(CC) -c mergesort.c -o mergesort.o

execution_time_utils.o: execution_time_utils.c
	$(CC) -c execution_time_utils.c -o execution_time_utils.o

clean: 
	rm execution_time_utils.o mergesort.o program