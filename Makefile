all: main

main: main.cpp src/* include/*
	g++ main.cpp src/Game/* -lncurses -o bin/main