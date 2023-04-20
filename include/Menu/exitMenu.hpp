// menu.h
#pragma once
#include <ncurses.h>
#include <vector>
#include <string>

class ExitMenu
{
private:
  WINDOW *menu_window;
  std::vector<std::string> items;
  int selected_index;
  int width, height;

public:
  ExitMenu(int width, int height);
  ~ExitMenu();

  void AddItem(std::string text);
  int GetChoice();
  void initialize(char loser);
  void refresh();
  void refreshMenu();
  void construct(int height, int width);
  void printResult(char loser);
};