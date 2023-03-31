all: main

main: main.cpp src/Board.hpp src/Game.hpp
	g++ main.cpp -lncurses -o bin/main