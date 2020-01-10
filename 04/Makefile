CC=g++ -std=c++14

all: matrix

matrix: matrix.o main.o
	$(CC) matrix.o main.o -o matrix

main.o: main.cpp
	 $(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
matrix.o: matrix.cpp
	 $(CC) -c matrix.cpp	 
	 
test: matrix.o test.o 
	$(CC) matrix.o test.o -o test_example
	./test_example
	rm -rf test.o test_example	 
	
run:
	 ./matrix 

clean:
	rm -rf *.o matrix test_example