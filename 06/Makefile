CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -g
TEST_LIB=-lgtest -lgtest_main -lpthread

all: program

tests.o: format.hpp
	$(CC) $(FLAGS) -c tests.cpp

program: format.hpp tests.o
	$(CC)  $(FLAGS) tests.o format.hpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm *.o test_bin



