#pragma once
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "Drawable.hpp"

/**
 * A section of a racer. Has a location and an icon.
 * @see Racer()
 */
class RacerPiece : public Drawable
{
public:
    RacerPiece();

    RacerPiece(int y, int x, chtype icon);

    // adds >> and << operators for RacerPiece objects
    friend std::ofstream &operator<<(std::ofstream &ofs, RacerPiece s);
    friend std::ifstream &operator>>(std::ifstream &ifs, RacerPiece &s);
};