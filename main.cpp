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
    static int BOARD_ROWS = 20;
    static int BOARD_COLS = BOARD_ROWS * 2.5;

    initscr();
    refresh();
    noecho();
    curs_set(0);

    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    if (maxY > BOARD_ROWS && maxX > BOARD_COLS)
    {
        Menu menu(BOARD_ROWS, BOARD_COLS);
        menu.printLogo();
        menu.AddItem("Start Game");
        menu.AddItem("Load Game");
        menu.AddItem("Quit");

        // refresh to show initial screen
        menu.refreshMenu();

        /* GetChoice needs ran before game creation to stop screen buffering */
        int choice = menu.GetChoice();

        Game game(BOARD_ROWS, BOARD_COLS);

        if (choice == 0) {
            // Starts the game.
            int gameRunning = 1;
            while (gameRunning) {
                while (!game.isOver())
                {
                    game.processInput();
                    game.updateState();
                    game.redraw();
                }

                ExitMenu exitMenu(BOARD_ROWS, BOARD_COLS);
                exitMenu.printResult(game.getLoser());
                exitMenu.AddItem("Restart");
                exitMenu.AddItem("Quit");
                exitMenu.refreshMenu();
                int exitChoice = exitMenu.GetChoice();
                
                if (exitChoice == 0) {
                    game.initialize();
                    // Game newgame(BOARD_ROWS, BOARD_COLS);
                    // game = newgame;
                } else {
                    gameRunning = 0;
                }
            }
        } else if (choice == 1) {
            game.loadGame();
        }
        endwin();
        
        // switch (choice)
        // {
        // case 0:
        //     // Starts the game.
        //     int gameRunning = 1;
        //     while (gameRunning) {
        //         while (!game.isOver())
        //         {
        //             game.processInput();
        //             game.updateState();
        //             game.redraw();
        //         }

        //         ExitMenu exitMenu(BOARD_ROWS, BOARD_COLS);
        //         exitMenu.printResult();
        //         exitMenu.AddItem("Restart");
        //         exitMenu.AddItem("Quit");
        //         exitMenu.refreshMenu();
        //         int exitChoice = exitMenu.GetChoice();
                
        //         if (exitChoice == 0) {
        //             Game newgame(BOARD_ROWS, BOARD_COLS);
        //             game = newgame;
        //         } else {
        //             gameRunning = 0;
        //         }
        //     }
        //     break;
        // case 1:
        //     // Exits the game.
        //     break;
        // }
        // endwin();
    }
    else
    {
        endwin();
        std::cout << std::endl
                  << "Please make sure your window is at least "
                  << BOARD_ROWS << " x " << BOARD_COLS
                  << " characters." << std::endl;
    }

    return 0;
}
