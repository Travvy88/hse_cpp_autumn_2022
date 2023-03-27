CC=g++-10
FLAGS=-std=c++20 #-Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: compile run_tests clean

compile: serializer.hpp deserializer.hpp error.hpp
	$(CC) $(FLAGS) tests.cpp -o test_bin $(TEST_LIB)

run_tests:
	./test_bin

clean:
	rm test_bin
