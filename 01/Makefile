CC=g++-10
FLAGS=-std=c++20
TEST_LIB=-lgtest -lgtest_main -lpthread

all: allocator test_bin test

allocator: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c allocator.cpp -o allocator


test_bin: allocator.o tests.o
	$(CC) $(FLAGS) allocator.o tests.o -o test_bin $(TEST_LIB)

tests.o: allocator.hpp
	$(CC) $(FLAGS) -c tests.cpp 
test:
	./test_bin

clean:
	rm -f *.o test_bin allocator

allocator_only:
	$(CC) $(FLAGS) allocator.cpp -o allocator

