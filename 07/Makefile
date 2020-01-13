CC=g++ -std=c++14

all: format

format: format.o main.o
	$(CC) format.o main.o -o format

main.o: main.cpp
	 $(CC) -c main.cpp
	 
format.o: format.cpp
	 $(CC) -c format.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
test: format.o test.o 
	$(CC) format.o test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./format 

clean:
	rm -rf *.o format test_example
    