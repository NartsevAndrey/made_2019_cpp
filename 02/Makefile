CC=g++

all: allocator.o

allocator.o: allocator.cpp
	 $(CC) -c allocator.cpp

test.o: test.cpp
	 $(CC) -c test.cpp
	 
clean:
	rm -rf *.o test_example	 
	 
test: test.o allocator.o
	$(CC)  test.o allocator.o -o test_example
	./test_example
	rm -rf test.o test_example	 
