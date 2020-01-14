CC=g++ -std=c++14 -pthread 

all: threadpool

threadpool: threadpool.o main.o
	$(CC) threadpool.o main.o -o threadpool

main.o: main.cpp
	$(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
threadpool.o: threadpool.cpp
	 $(CC) -c threadpool.cpp	 
	 
test: threadpool.o test.o 
	$(CC) threadpool.o test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./threadpool 

clean:
	rm -rf *.o threadpool test_example
    