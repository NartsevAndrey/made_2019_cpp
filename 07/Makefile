CC=g++ -std=c++14

all: format

format: main.o
	$(CC) main.o -o format

main.o: main.cpp
	 $(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
test: test.o 
	$(CC) test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./format 

clean:
	rm -rf *.o format test_example
    