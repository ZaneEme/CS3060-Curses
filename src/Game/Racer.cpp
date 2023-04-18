#include <ncurses.h>
#include <queue>
#include <sstream>
#include <string>
#include "../../include/Game/Racer.hpp"
#include "../../include/Game/RacerPiece.hpp"

/**
 * Main section of the racer. Consists of a symbol and a queue of type RacerPiece.
 * @see RacerPiece()
 */

Racer::Racer()
{
    symbol = '#';
    cur_dir = down;
}

Racer::Racer(chtype icon)
{
    cur_dir = down;
    symbol = icon;
}

void Racer::addPiece(RacerPiece piece)
{
    prev_pieces.push(piece);
}

void Racer::removePiece()
{
    prev_pieces.pop();
}

RacerPiece Racer::tail()
{
    return prev_pieces.front();
}

RacerPiece Racer::head()
{
    return prev_pieces.back();
}

Direction Racer::getDirection()
{
    return cur_dir;
}

chtype Racer::getSymbol()
{
    return symbol;
}

/**
 * If the new direction isn't opposite of the current direction
 * and sets accordingly.
 * @param dir the attempted direction to change to
 * @see Direction{}
 */
void Racer::setDirection(Direction dir)
{
    if (cur_dir + dir != 0)
        cur_dir = dir;
}

/**
 * Creates a RacerPiece at the next location based on direction.
 * @see Direction{}
 * @see RacerPiece
 * @return a RacerPiece at the next location
 */
RacerPiece Racer::nextHead()
{
    int row = head().getY();
    int col = head().getX();

    switch (cur_dir)
    {
    case down:
        row++;
        break;
    case up:
        row--;
        break;
    case left:
        col--;
        break;
    case right:
        col++;
        break;
    }
    return RacerPiece(row, col, this->symbol);
}