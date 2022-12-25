CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: main

main:
	$(CC) $(FLAGS) main.cpp -o main
	./main
	rm main

clean:
	rm main
