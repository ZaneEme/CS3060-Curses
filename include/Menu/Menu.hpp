// menu.h
#pragma once
#include <ncurses.h>
#include <vector>
#include <string>

class Menu
{
private:
  WINDOW *menu_window;
  std::vector<std::string> items;
  int selected_index;
  int width, height;

public:
  Menu(int width, int height);
  ~Menu();

  void AddItem(std::string text);
  int GetChoice();
  void refresh();
  void initialize();
  void refreshMenu();
  void construct(int height, int width);
  void printLogo();
};