#include "../../include/Game/Board.hpp"
#include "../../include/Game/Drawable.hpp"
#include <stdlib.h>
#include <ncurses.h>

/**
 * Creates a new board with 0 width and 0 height.
 */
Board::Board()
{
    construct(0, 0);
}
/**
 * Creates a board with given width and height.
 * @param height,width the size of the board to be created
 * @see Board()
 */
Board::Board(int height, int width)
{
    construct(height, width);
}

/**
 * Clears the screen and refreshes the buffer.
 */
void Board::initialize()
{
    clear();
    refresh();
}

/**
 * Adds a border around the board
 */
void Board::addBorder()
{
    box(board_win, 0, 0);
}

/**
 * Add a drawable to the board at it's location.
 * @param drawable the piece to be added to the board
 */
void Board::add(Drawable drawable)
{
    addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
}

/**
 * Adds a char to the board at a given location.
 * @param y,x the location of the char
 * @param ch the char to be drawn
 */
void Board::addAt(int y, int x, chtype ch)
{
    mvwaddch(board_win, y, x, ch);
}

chtype Board::getInput()
{
    return wgetch(board_win);
}

/**
 * Returns the char at a given location
 * @param y,x the location to search
 * @returns the char on the board at y,x
 */
chtype Board::getCharAt(int y, int x)
{
    return mvwinch(board_win, y, x);
}

void Board::clear()
{
    wclear(board_win);
}

/**
 * Ensures a border is added and refreshes the screen.
 */
void Board::refresh()
{
    addBorder();
    wrefresh(board_win);
}
/**
 * Sets the timeout for awaiting an input.
 */
void Board::setTimeout(int timeout)
{
    wtimeout(board_win, timeout);
}

/**
 * Creates a board window with terminal-size adjustments.
 * Sets timeout of game, and disables echo of keypresses.
 * @param height,width the size of the board to be created.
 * @see Board()
 */
void Board::construct(int height, int width)
{
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    this->height = height;
    this->width = width;

    board_win = newwin(height, width, (maxY / 2) - (height / 2), (maxX / 2) - (width / 2));
    setTimeout(300);
    keypad(board_win, true);
}