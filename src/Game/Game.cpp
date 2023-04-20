#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "../../include/Game/Board.hpp"
#include "../../include/Game/Racer.hpp"
#include "../../include/Game/RacerPiece.hpp"
#include "../../include/Game/Game.hpp"

void Game::runGame()
{
    while (!isOver())
    {
        processInput();
        updateState();
        redraw();
    }
}

/**
 * Checks if a the next piece will hit a wall or the enemy,
 * if not adds to the head of the racer.
 * @param racer The racer "train" to check against
 * @param next  The piece to be added if all checks pass
 */
void Game::handleNextPlace(Racer &racer, RacerPiece next)
{
    if (board.getCharAt(next.getY(), next.getX()) != ' ')
    {
        game_over = true;
        loser = racer.getSymbol();
    }
    // add piece to front
    board.add(next);
    racer.addPiece(next);
}

/**
 * Creates a new board and initializes it.
 * @param height,width the size of the board in chars
 */
Game::Game(int height, int width)
{
    board = Board(height, width);
    initialize();
}

/**
 * Sets up the board, places racer A and racer B in top corners.
 * @see Game()
 */
void Game::initialize()
{
    racerA = Racer('#');
    racerB = Racer('*');
    board.initialize();
    game_over = false;
    loser = ' ';

    // racer A
    racerA.setDirection(down);
    handleNextPlace(racerA, RacerPiece(1, 3, racerA.getSymbol()));
    handleNextPlace(racerA, racerA.nextHead());
    handleNextPlace(racerA, racerA.nextHead());
    racerA.setDirection(right);
    handleNextPlace(racerA, racerA.nextHead());

    // racer B
    racerB.setDirection(down);
    handleNextPlace(racerB, RacerPiece(1, 45, racerB.getSymbol()));
    handleNextPlace(racerB, racerB.nextHead());
    handleNextPlace(racerB, racerB.nextHead());
    racerB.setDirection(left);
    handleNextPlace(racerB, racerB.nextHead());
}

/**
 * Changes direction for racers based on WASD or arrow keys.
 */
void Game::processInput()
{
    chtype input = board.getInput();

    switch (input)
    {
    case KEY_UP:
        racerB.setDirection(up);
        break;
    case 'w':
        racerA.setDirection(up);
        break;
    case KEY_DOWN:
        racerB.setDirection(down);
        break;
    case 's':
        racerA.setDirection(down);
        break;
    case KEY_RIGHT:
        racerB.setDirection(right);
        break;
    case 'd':
        racerA.setDirection(right);
        break;
    case KEY_LEFT:
        racerB.setDirection(left);
        break;
    case 'a':
        racerA.setDirection(left);
        break;
    case 'r':
        saveGame();
        redraw();
        break;
    case 'p':
        board.setTimeout(-1);
        while (board.getInput() != 'p')
            ;
        board.setTimeout(300);
        break;
    case 'q':
        game_over = true;
        break;
    default:
        break;
    }
}

/**
 * Places new heads for each racer and checks collisions.
 * @see handleNextPlace()
 */
void Game::updateState()
{
    handleNextPlace(racerA, racerA.nextHead());
    handleNextPlace(racerB, racerB.nextHead());
}

void Game::redraw()
{
    board.refresh();
}

bool Game::isOver()
{
    return game_over;
}

char Game::getLoser()
{
    return loser;
}

void Game::saveGame()
{
    try
    {
        // Open the files for writing.
        std::ofstream racerOne("bin/racerOne.csv", std::ios::trunc);
        std::ofstream racerTwo("bin/racerTwo.csv", std::ios::trunc);

        racerOne << this->racerA;
        racerTwo << this->racerB;

        racerOne.close();
        racerTwo.close();
    }
    catch (std::exception &e)
    {
        std::cerr << "File could not be saved! Exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    }
}

/**
 * Reads from bin/racerOne and bin/racerTwo into the two racer objects
 */
void Game::loadGame()
{
    try
    {
        racerA.clear();
        racerB.clear();
        // Open the files for reading.
        std::ifstream racerOne("bin/racerOne.csv");
        std::ifstream racerTwo("bin/racerTwo.csv");

        racerOne >> this->racerA;
        racerTwo >> this->racerB;

        racerOne.close();
        racerTwo.close();

        for (RacerPiece i : racerA.getBody()) {
            board.add(i);
        }
        for (RacerPiece i : racerB.getBody()) {
            board.add(i);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "File could not be loaded! Exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    }
    redraw();
}
