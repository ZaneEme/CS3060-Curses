all: main

main: main.cpp src/* include/*
	g++ main.cpp src/Game/* src/Menu/* -lncurses -o bin/main