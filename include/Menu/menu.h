// menu.h

#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

class Menu {
 public:
  Menu(int x, int y, int width, int height);
  ~Menu();

  void AddItem(std::string text);
  void SetSelectedIndex(int index);
  std::string GetSelectedItem();
  int GetChoice();

 private:
  WINDOW *menu_window;
  std::vector<struct MenuEntry> items;
  int selected_index;

  struct MenuEntry {
    std::string text;
    int value;
  };
};

#endif // MENU_H