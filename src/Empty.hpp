#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
/**
 * An empty character that serves as a placeholder on the board
 */
class Empty : public Drawable
{
public:
    /**
     * The default constructor.
     * @param y,x the location of the empty slot
     */
    Empty(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = ' ';
    }
};