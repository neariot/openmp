CXX = gcc
CXXFLAGS= -fopenmp
all: hello
hello: openmp.cpp
	$(CXX) $(CXXFLAGS) openmp.cpp -o hello
clean:
	rm hello
