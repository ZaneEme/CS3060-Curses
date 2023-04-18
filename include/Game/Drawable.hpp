#pragma once
#include <ncurses.h>

/**
 * A base class for objects written to the board.
 * All subclasses must include a location and a char.
 */
class Drawable
{
public:
    Drawable();

    Drawable(int y, int x, chtype icon);

    int getX();
    int getY();
    chtype getIcon();

    void setX(int x);
    void setY(int y);
    void setIcon(chtype icon);

protected:
    int y, x;
    chtype icon;
};