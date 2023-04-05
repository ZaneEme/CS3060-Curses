#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "Board.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"

class Game {
    Board board;
    bool game_over;
    Apple *apple;
    Snake snake;

    void createApple() {
        int y, x;
        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);
    }

    void destroyApple() {
        delete apple;
        apple = NULL;
    }

    void handleNextPlace(SnakePiece next) {
        if (apple != NULL) {
            switch (board.getCharAt(next.getY(), next.getX())) {
                case 'A':
                    destroyApple();
                    break;
                case ' ': 
                {
                    // remove a part from the tail
                    int emptyRow = snake.tail().getY();
                    int emptyCol = snake.tail().getX();
                    board.add(Empty(emptyRow, emptyCol));
                    snake.removePiece();
                    break;
                }
                default:
                    game_over = true;
                    break;
            }
        }
        // add piece to front
        board.add(next);
        snake.addPiece(next);
    }

public:
    Game(int height, int width) {
        board = Board(height, width);
        initialize();
    }

    ~Game() {
        delete apple;
    }

    void initialize() {
        apple = NULL; 
        board.initialize();
        game_over = false;
        srand(time(NULL));

        snake.setDirection(down);

        handleNextPlace(SnakePiece(1, 1));

        handleNextPlace(snake.nextHead());
        handleNextPlace(snake.nextHead());

        snake.setDirection(right);
        handleNextPlace(snake.nextHead());

        if (apple == NULL) {
            createApple();
        }
    }

    void processInput() {
        chtype input = board.getInput();

        switch(input) {
            case KEY_UP:
            case 'w':
                snake.setDirection(up);
                break;
            case KEY_DOWN:
            case 's':
                snake.setDirection(down);
                break;
            case KEY_RIGHT:
            case 'd':
                snake.setDirection(right);
                break;
            case KEY_LEFT:
            case 'a':
                snake.setDirection(left);
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
        handleNextPlace(snake.nextHead());

        if (apple == NULL) {
            createApple();
        }
    }

    void redraw() {
        board.refresh();
    }

    bool isOver() {
        return game_over;
    }
};