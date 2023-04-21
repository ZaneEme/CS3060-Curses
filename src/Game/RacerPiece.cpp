#include <ncurses.h>
#include <queue>
#include <sstream>
#include <string>
#include "../../include/Game/RacerPiece.hpp"

/**
 * A section of a racer. Has a location and an icon.
 * @see Racer()
 */
RacerPiece::RacerPiece()
{
    this->x = this->y = 0;
    this->icon = '#';
}
RacerPiece::RacerPiece(int y, int x, chtype icon)
{
    this->y = y;
    this->x = x;
    this->icon = icon;
}

/**
 * Overloads the << operator to write a RacerPiece to a given ofstream
 * Ex: ofstream << RacerPiece writes:
 *  x,y,icon to the stream
 */
std::ofstream &operator<<(std::ofstream &ofs, RacerPiece r)
{
    ofs << std::to_string(r.getY()) << ',' << r.getX() << ',' << r.getIcon() << std::endl;
    return ofs;
}

/**
 * Overloads the >> operator to read from a given ifstream to a RacerPiece
 * Ex: ifstream >> RacerPiece
 */
std::ifstream &operator>>(std::ifstream &ifs, RacerPiece &r)
{
    std::string line;

    if (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        std::string token;

        if (std::getline(ss, token, ','))
        {
            r.setY(stoi(token));
        }

        if (std::getline(ss, token, ','))
        {
            r.setX(stoi(token));
        }

        if (std::getline(ss, token, ','))
        {
            r.setIcon((chtype)token[0]);
        }
    }
    return ifs;
}