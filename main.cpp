#include <iostream>
#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Game.hpp"
#include "src/Drawable.hpp"
/**
 * Will be the main runner class everything branches from
*/

int main(int argc, char **argv) {
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;

    initscr();
    refresh();  

    noecho();
    curs_set(0);

    Game game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver()) {
        game.processInput();
        game.updateState();

        game.redraw();
    }
    endwin();

    std::cout << "Game over!" << std::endl;

    return 0;
}