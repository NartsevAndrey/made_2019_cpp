CC=g++ -std=c++14

all: vector

vector: main.o
	$(CC)  main.o -o vector

main.o: main.cpp
	 $(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
test: test.o 
	$(CC) test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./vector 

clean:
	rm -rf *.o vector test_example
    