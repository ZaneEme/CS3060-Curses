#pragma once
#include <ncurses.h>
#include <queue>
#include "Drawable.hpp"

/**
 * Stores the four possible directions a racer can be facing.
 */
enum Direction
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
};

/**
 * A section of a racer. Has a location and an icon.
 * @see Racer()
 */
class RacerPiece : public Drawable
{
public:
    RacerPiece();

    RacerPiece(int y, int x, chtype icon);
};

/**
 * Main section of the racer. Consists of a symbol and a queue of type RacerPiece.
 * @see RacerPiece()
 */
class Racer
{
private:
    std::queue<RacerPiece> prev_pieces;
    Direction cur_dir;
    chtype symbol;

public:
    Racer();

    Racer(chtype icon);

    void addPiece(RacerPiece piece);

    void removePiece();

    RacerPiece tail();

    RacerPiece head();

    Direction getDirection();

    chtype getSymbol();

    /**
     * If the new direction isn't opposite of the current direction
     * and sets accordingly.
     * @param dir the attempted direction to change to
     * @see Direction{}
     */
    void setDirection(Direction dir);

    /**
     * Creates a RacerPiece at the next location based on direction.
     * @see Direction{}
     * @see RacerPiece
     * @return a RacerPiece at the next location
     */
    RacerPiece nextHead();
};