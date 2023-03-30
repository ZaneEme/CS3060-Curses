#pragma once
class Board {
public:
    Board(int height, int width) {
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);

        board_win = newwin(height, width, (maxY / 2) - (height / 2), (maxX / 2) - (width / 2));
        
    }
    
    void initialize() {
        clear();
        refresh();
    }

    void addBorder() {
        box(board_win, 0, 0);
    }

    void clear() {
        wclear(board_win);
        addBorder();
    }

    void refresh() {
        wrefresh(board_win);
    }

private:
    WINDOW *board_win;
};