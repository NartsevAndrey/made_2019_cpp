CC=g++

all: calculation

calculation: calc.o main.o
	$(CC) calc.o main.o -o calc

main.o: main.cpp
	 $(CC) -c main.cpp
	 
calc.o: calc.cpp
	 $(CC) -c calc.cpp

test.o: test.cpp
	 $(CC) -c test.cpp
	 
clean:
	rm -rf *.o calc test_example	 
	 
test: test.o calc.o
	$(CC)  test.o calc.o -o test_example
	./test_example
	rm -rf test.o test_example	 
	
ifeq (run, $(firstword $(MAKECMDGOALS)))
  runargs := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(runargs):;@true)
endif	
	
run:
	 ./calc $(runargs)
%:
	@:
