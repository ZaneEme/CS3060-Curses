#include <iostream>
#include <ncurses.h>
#include "include/Game/Board.hpp"
#include "include/Game/Game.hpp"
#include "include/Menu/Menu.hpp"
#include "include/Menu/ExitMenu.hpp"

/**
 * Responsible for the main loop and ending the game.
 * @return The cli exit code
 */
int main(int argc, char **argv)
{
    // Creates the size of the board
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;

    // Init curses
    initscr();
    refresh();
    noecho();
    curs_set(0);

    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    // Error if the user doesn't have a large enough screen.
    if (maxY < BOARD_ROWS || maxX < BOARD_COLS)
    {
        endwin();
        std::cout << std::endl
                  << "Please make sure your window is at least "
                  << BOARD_ROWS << " x " << BOARD_COLS
                  << " characters." << std::endl;

        return 1;
    }

    Menu menu(BOARD_ROWS, BOARD_COLS);
    menu.initialize();
    // refresh to show initial screen
    menu.refreshMenu();

    /* GetChoice needs ran before game creation to stop screen buffering */
    int choice = menu.GetChoice();

    Game game(BOARD_ROWS, BOARD_COLS);

    // Takes user input based on start menu
    switch (choice)
    {
    case 1:
        game.loadGame();
        game.redraw();
    case 0:
        // Starts the game.
        int gameRunning = 1;
        while (gameRunning)
        {
            game.runGame();

            ExitMenu exitMenu(BOARD_ROWS, BOARD_COLS);
            exitMenu.initialize(game.getLoser());

            if (exitMenu.GetChoice() == 0)
            {
                game.initialize();
            }
            else
            {
                gameRunning = 0;
            }
        }
    }
    endwin();
    return 0;
}