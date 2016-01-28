CC = gcc
CFLAGS= -fopenmp
all: hello
hello: openmp.c
	$(CC) $(CFLAGS) openmp.c -o hello
clean:
	rm hello