all: main

main: main.cpp src/Board.hpp
	g++ main.cpp -lncurses -o bin/main