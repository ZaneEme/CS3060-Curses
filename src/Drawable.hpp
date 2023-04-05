#pragma once
#include <ncurses.h>

/**
 * A base class for objects written to the board.
 * All subclasses must include a location and a char.
 */
class Drawable
{
public:
    Drawable()
    {
        y = x = 0;
        icon = ' ';
    }

    Drawable(int y, int x, chtype icon)
    {
        this->y = y;
        this->x = x;
        this->icon = icon;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    chtype getIcon()
    {
        return icon;
    }

protected:
    int y, x;
    chtype icon;
};