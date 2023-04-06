#pragma once
#include <ncurses.h>

class Drawable;
class Board
{
public:
    /**
     * Creates a new board with 0 width and 0 height.
     */
    Board();
    /**
     * Creates a board with given width and height.
     * @param height,width the size of the board to be created
     * @see Board()
     */
    Board(int height, int width);

    /**
     * Clears the screen and refreshes the buffer.
     */
    void initialize();

    /**
     * Adds a border around the board
     */
    void addBorder();

    /**
     * Add a drawable to the board at it's location.
     * @param drawable the piece to be added to the board
     */
    void add(Drawable drawable);

    /**
     * Adds a char to the board at a given location.
     * @param y,x the location of the char
     * @param ch the char to be drawn
     */
    void addAt(int y, int x, chtype ch);

    chtype getInput();

    /**
     * Returns the char at a given location
     * @param y,x the location to search
     * @returns the char on the board at y,x
     */
    chtype getCharAt(int y, int x);

    void clear();

    /**
     * Ensures a border is added and refreshes the screen.
     */
    void refresh();
    /**
     * Sets the timeout for awaiting an input.
     */
    void setTimeout(int timeout);

private:
    WINDOW *board_win;
    int height, width;

    /**
     * Creates a board window with terminal-size adjustments.
     * Sets timeout of game, and disables echo of keypresses.
     * @param height,width the size of the board to be created.
     * @see Board()
     */
    void construct(int height, int width);
};