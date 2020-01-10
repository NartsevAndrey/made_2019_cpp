CC=g++ -std=c++14

all: serializer

serializer: serializer.o main.o
	$(CC) serializer.o main.o -o serializer

main.o: main.cpp
	 $(CC) -c main.cpp
	 
test.o: test.cpp
	 $(CC) -c test.cpp
	 
serializer.o: serializer.cpp
	 $(CC) -c serializer.cpp	 
	 
test: serializer.o test.o 
	$(CC) serializer.o test.o -o test_example
	./test_example
	rm -rf test.o test_example
	
run:
	 ./serializer 

clean:
	rm -rf *.o serializer test_example
    