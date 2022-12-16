CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: matrix test_bin test clean

matrix: matrix.cpp 
	$(CC) $(FLAGS) -c matrix.cpp -o matrix.o

test_bin: matrix.o tests.o
	 $(CC) $(FLAGS) matrix.o tests.o -o test_bin  $(TEST_LIB)

tests.o:
	$(CC) $(FLAGS) -c tests.cpp

test:
	./test_bin

clean:
	rm -r test_bin *.o
