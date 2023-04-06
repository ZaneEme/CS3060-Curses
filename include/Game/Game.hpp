#pragma once
#include <ncurses.h>
#include "Racer.hpp"
#include "Board.hpp"

class Game
{
    Board board;
    bool game_over;
    chtype loser;
    Racer racerA{'*'};
    Racer racerB{'#'};

    /**
     * Checks if a the next piece will hit a wall or the enemy,
     * if not adds to the head of the racer.
     * @param racer The racer "train" to check against
     * @param next  The piece to be added if all checks pass
     */
    void handleNextPlace(Racer &racer, RacerPiece next);

public:
    /**
     * Creates a new board and initializes it.
     * @param height,width the size of the board in chars
     */
    Game(int height, int width);

    /**
     * Sets up the board, places racer A and racer B in top corners.
     * @see Game()
     */
    void initialize();

    /**
     * Changes direction for racers based on WASD or arrow keys.
     */
    void processInput();

    /**
     * Places new heads for each racer and checks collisions.
     * @see handleNextPlace()
     */
    void updateState();

    void redraw();

    bool isOver();

    char getLoser();
};