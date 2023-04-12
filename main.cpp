#include <iostream>
#include <ncurses.h>
#include "include/Game/Board.hpp"
#include "include/Game/Game.hpp"
#include "include/Menu/menu.h"

/**
 * Responsible for the main loop and ending the game.
 * @return The cli exit code
 */
int main(int argc, char **argv)
{
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;

    initscr();
    refresh();
    noecho();
    curs_set(0);

    Game game(BOARD_ROWS, BOARD_COLS);

    Menu menu(10, 10, 30, 10);
    menu.AddItem("Start Game");
    menu.AddItem("Quit");

    int choice = menu.GetChoice();

    switch (choice) {
    case 0:
        // Starts the game.
        break;
    case 1:
        //Exits the game.
        //game_over = true;
        break;
    }

    while (!game.isOver())
    {
        game.processInput();
        game.updateState();
        game.redraw();
    }
    endwin();

    std::cout << "Game over! " << game.getLoser() << " loses!" << std::endl;

    return 0;
}