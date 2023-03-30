#include <ncurses.h>
#include "src/Board.hpp"
/**
 * Will be the main runner class everything branches from
*/

int main(int argc, char **argv) {
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;
    
    initscr();
    refresh();

    Board board(BOARD_ROWS, BOARD_COLS);
    board.initialize();

    getch();
    endwin();

    return 0;
}