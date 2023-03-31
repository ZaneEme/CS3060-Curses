#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Game.hpp"
/**
 * Will be the main runner class everything branches from
*/

int main(int argc, char **argv) {
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;

    initscr();
    refresh();

    noecho();

    Game game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver()) {
        game.processInput();
        game.updateState();

        game.redraw();


    }

    getch();
    endwin();

    return 0;
}