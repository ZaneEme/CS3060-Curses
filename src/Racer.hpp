#pragma once
#include <ncurses.h>
#include <queue>
#include "Drawable.hpp"

enum Direction {
    up = -1,
    down = 1,
    left = -2,
    right = 2
};

class RacerPiece : public Drawable {
public:
    RacerPiece() {
        this->x = this->y = 0;
        this->icon = '#';
    }
    RacerPiece(int y, int x, chtype icon) {
        this->y = y;
        this->x = x;
        this->icon = icon;
    }
};

class Racer {
private:
    std::queue<RacerPiece> prev_pieces;
    Direction cur_dir;
    chtype symbol;
public:
    Racer() {
        symbol = '#';
        cur_dir = down;
    }
    Racer(chtype icon) {
        cur_dir = down;
        symbol = icon;
    }

    void addPiece(RacerPiece piece) {
        prev_pieces.push(piece);
    }

    void removePiece() {
        prev_pieces.pop();
    }

    RacerPiece tail() {
        return prev_pieces.front();
    }

    RacerPiece head() {
        return prev_pieces.back();
    }

    Direction getDirection() {
        return cur_dir;
    }

    chtype getSymbol() {
        return symbol;
    }

    void setDirection(Direction dir) {
        if(cur_dir + dir != 0)
            cur_dir = dir;
    }

    RacerPiece nextHead() {
        int row = head().getY();
        int col = head().getX();

        switch (cur_dir) {
            case down:
                row++;
                break;
            case up:
                row--;
                break;
            case left:
                col--;
                break;
            case right:
                col++;
                break;
        }
        return RacerPiece(row, col, this->symbol);
    }
};