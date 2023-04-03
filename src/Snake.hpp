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

class SnakePiece : public Drawable {
public:
    SnakePiece() {
        this->x = this->y = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x) {
        this->y = y;
        this->x = x;
        this->icon = '#';
    }
};

class Snake {
    std::queue<SnakePiece> prev_pieces;
    Direction cur_dir;
public:
    Snake() {
        cur_dir = down;
    }

    void addPiece(SnakePiece piece) {
        prev_pieces.push(piece);
    }

    void removePiece() {
        prev_pieces.pop();
    }

    SnakePiece tail() {
        return prev_pieces.front();
    }

    SnakePiece head() {
        return prev_pieces.back();
    }

    Direction getDirection() {
        return cur_dir;
    }

    void setDirection(Direction dir) {
        if(cur_dir + dir != 0)
            cur_dir = dir;
    }

    SnakePiece nextHead() {
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
        return SnakePiece(row, col);
    }
};