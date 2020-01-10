CC=g++ -std=c++14

all: bigint

bigint: bigint.o main.o
	$(CC) bigint.o main.o -o bigint

main.o: main.cpp
	 $(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
bigint.o: bigint.cpp
	 $(CC) -c bigint.cpp	 
	 
test: bigint.o test.o 
	$(CC) bigint.o test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./bigint 

clean:
	rm -rf *.o bigint test_example
    