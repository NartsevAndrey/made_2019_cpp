CC=g++ -std=c++14

all: parsing

parsing: parser.o main.o
	$(CC) parser.o main.o -o parser

main.o: main.cpp
	 $(CC) -c main.cpp
	 
parser.o: parser.cpp
	 $(CC) -c parser.cpp

test.o: test.cpp
	 $(CC) -c test.cpp
	 
clean:
	rm -rf *.o parser test_example	 
	 
test: test.o parser.o
	$(CC)  test.o parser.o -o test_example
	./test_example
	rm -rf test.o test_example	 
	
ifeq (run, $(firstword $(MAKECMDGOALS)))
  runargs := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(runargs):;@true)
endif	
	
run:
	 ./parser $(runargs)
%:
	@:
