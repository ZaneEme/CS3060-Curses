all: main

main: main.cpp src/*
	g++ main.cpp -lncurses -o bin/main