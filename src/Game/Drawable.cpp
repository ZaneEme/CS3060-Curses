#include <ncurses.h>
#include "../../include/Game/Drawable.hpp"
/**
 *
 * A base class for objects written to the board.
 * All subclasses must include a location and a char.
 */

Drawable::Drawable()
{
    y = x = 0;
    icon = ' ';
}

Drawable::Drawable(int y, int x, chtype icon)
{
    this->y = y;
    this->x = x;
    this->icon = icon;
}

int Drawable::getX()
{
    return x;
}

int Drawable::getY()
{
    return y;
}

chtype Drawable::getIcon()
{
    return icon;
}
