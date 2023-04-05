#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "Board.hpp"
#include "Empty.hpp"
#include "Drawable.hpp"
#include "Racer.hpp"

class Game {
    Board board;
    bool game_over;
    chtype loser;
    Racer racerA{'*'};
    Racer racerB{'#'};


    void handleNextPlace(Racer &racer, RacerPiece next) {
        if (board.getCharAt(next.getY(), next.getX()) != ' ') {
            game_over = true;
            loser = racer.getSymbol();
        }
        // add piece to front
        board.add(next);
        racer.addPiece(next);
    }

public:
    Game(int height, int width) {
        board = Board(height, width);
        initialize();
    }


    void initialize() { 
        board.initialize();
        game_over = false;
        loser = ' ';
        srand(time(NULL));

        // racer A
        racerA.setDirection(down);
        handleNextPlace(racerA, RacerPiece(1, 1, racerA.getSymbol()));
        handleNextPlace(racerA, racerA.nextHead());
        handleNextPlace(racerA, racerA.nextHead());
        racerA.setDirection(right);
        handleNextPlace(racerA, racerA.nextHead());

        // racer B
        racerB.setDirection(down);
        handleNextPlace(racerB, RacerPiece(1, 45, racerB.getSymbol()));
        handleNextPlace(racerB, racerB.nextHead());
        handleNextPlace(racerB, racerB.nextHead());
        racerB.setDirection(left);
        handleNextPlace(racerB, racerB.nextHead());

    }

    void processInput() {
        chtype input = board.getInput();

        switch(input) {
            case KEY_UP:
                racerB.setDirection(up);
                break;
            case 'w':
                racerA.setDirection(up);
                break;
            case KEY_DOWN:
                racerB.setDirection(down);
                break;
            case 's':
                racerA.setDirection(down);
                break;
            case KEY_RIGHT:
                racerB.setDirection(right);
                break;
            case 'd':
                racerA.setDirection(right);
                break;
            case KEY_LEFT:
                racerB.setDirection(left);
                break;
            case 'a':
                racerA.setDirection(left);
                break;
            case 'p':
                board.setTimeout(-1);
                while(board.getInput() != 'p');
                board.setTimeout(300);
                break;
            default:
                break;
        }
    }

    void updateState() {
        handleNextPlace(racerA, racerA.nextHead());
        handleNextPlace(racerB, racerB.nextHead());
    }

    void redraw() {
        board.refresh();
    }

    bool isOver() {
        return game_over;
    }

    char getLoser() {
        return loser;
    }
};