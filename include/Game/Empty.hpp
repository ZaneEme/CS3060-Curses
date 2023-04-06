#pragma once
#include <ncurses.h>

#include "Drawable.hpp"

/**
 * An empty character that serves as a placeholder on the board
 */
class Empty : public Drawable
{
private:
int x;
int y;
chtype icon;
public:
    /**
     * The default constructor.
     * @param y,x the location of the empty slot
     */
    Empty(int y, int x);
};