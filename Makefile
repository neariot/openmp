CC = gcc
CXXFLAGS= -fopenmp
all: hello
hello: openmp.cpp
	$(CC) $(CXXFLAGS) openmp.cpp -o hello -std=c11
clean:
	rm hello
