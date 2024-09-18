CC=gcc

mergesort: mergesort.o libs/memory_allocation_utils.o libs/wr_operations.o libs/utils.o
	$(CC) mergesort.o libs/memory_allocation_utils.o libs/wr_operations.o libs/utils.o -o mergesort

mergesort.o: mergesort.c libs/memory_allocation_utils.o libs/wr_operations.o
	$(CC) -c mergesort.c -o mergesort.o

wr_operations.o: libs/wr_operations.c libs/memory_allocation_utils.o
	$(CC) -c libs/wr_operations.c -o libs/wr_operations.o

memory_allocation_utils.o: libs/memory_allocation_utils.c libs/memory_allocation_utils.h
	$(CC) -c libs/memory_allocation_utils.c -o libs/memory_allocation_utils.o

utils.o: utils.c
	$(CC) -c libs/utils.c -o utils.o


clean: 
	rm libs/memory_allocation_utils.o mergesort.o libs/wr_operations.o