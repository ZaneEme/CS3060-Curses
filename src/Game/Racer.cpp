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
    prev_pieces.push_front(piece);
}

void Racer::clear() {
    prev_pieces.clear();
}

RacerPiece Racer::tail()
{
    return prev_pieces.back();
}

std::deque<RacerPiece> Racer::getBody() {
    return prev_pieces;
}

RacerPiece Racer::head()
{
    return prev_pieces.front();
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

/**
 * Overloads the << operator to write a Racer to a given ofstream
 * Ex: ofstream << Racer writes:
 *  x,y,icon to the stream
 */
std::ofstream &operator<<(std::ofstream &ofs, Racer r)
{
    std::deque<RacerPiece> body = r.getBody();
    for(auto piece = body.end(); piece != body.begin(); piece--) {
        ofs << std::to_string(piece->getY()) << ',' << piece->getX() << ',' << piece->getIcon() << std::endl;
    }
    return ofs;
}

std::ifstream &operator>>(std::ifstream &ifs, Racer &r)
{
    std::string line;
    while (std::getline(ifs, line))
    {   
        std::stringstream ss(line);
        std::string token;
        RacerPiece piece;

        if (std::getline(ss, token, ','))
        {
            piece.setY(stoi(token));
        }

        if (std::getline(ss, token, ','))
        {
            piece.setX(stoi(token));
        }

        if (std::getline(ss, token, ','))
        {
            int ascii = std::stoi(token);
            piece.setIcon((chtype)static_cast<char>(ascii));
        }
        r.addPiece(piece);
    }
    return ifs;
}