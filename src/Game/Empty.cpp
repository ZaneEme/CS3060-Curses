#include "../../include/Game/Empty.hpp"

/**
 * The default constructor.
 * @param y,x the location of the empty slot
 */
Empty::Empty(int y, int x)
{
    this->y = y;
    this->x = x;
    this->icon = ' ';
}