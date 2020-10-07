# Jia Ling Chan
# Majid Zare
# CSE 374 - HW 6
# Makefile
# 5/19/2020

CC = gcc -Wall -g -std=c11
FILES = getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o

# default target
all: bench

# the executable
bench: bench.o $(FILES)
		$(CC) -o bench bench.c $(FILES)

# the individual source files
bench.o: bench.c mem.h
		$(CC) -c bench.c

getmem.o: getmem.c mem.h mem_impl.h
		$(CC) -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
		$(CC) -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
		$(CC) -c get_mem_stats.c

print_heap.o: print_heap.c mem.h
		$(CC) -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
		$(CC) -c mem_utils.c

# remove built files and backups
clean:
		rm -f *.o bench *~
