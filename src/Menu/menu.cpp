#include <ncurses.h>
#include <string>
#include "../../include/Menu/Menu.hpp"

Menu::Menu(int height, int width)
{
  cbreak();
  construct(height, width);
  box(menu_window, 0, 0);
  refreshMenu();
}

void Menu::refreshMenu()
{
  for (int i = 0; i < int(items.size()); i++)
  {
    if (i == selected_index)
    {
      wattron(menu_window, A_REVERSE);
    }

    mvwaddstr(menu_window, (height / 2) + i, (width / 2) - (items[i].length() / 2), items[i].c_str());
    wattroff(menu_window, A_REVERSE);
  }
  refresh();
}

Menu::~Menu()
{
  delwin(menu_window);
  endwin();
}

void Menu::AddItem(std::string text)
{
  items.push_back(text);
}

/**
 * Loops until user presses enter, arrow keys change options
 */
int Menu::GetChoice()
{
  chtype key;
  selected_index = 0;

  while (key != '\n')
  {
    // Refresh data
    refreshMenu();

    key = wgetch(menu_window);

    // if up and not at top
    if (key == KEY_UP && selected_index > 0)
    {
      selected_index--;
    }
    // if down and not at bottom
    else if (key == KEY_DOWN && selected_index < int(items.size() - 1))
    {
      selected_index++;
    }
  }
  return selected_index;
}

void Menu::refresh()
{
  box(menu_window, 0, 0);
  wrefresh(menu_window);
}

void Menu::construct(int height, int width)
{
  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);
  this->height = height;
  this->width = width;

  menu_window = newwin(height, width, (maxY / 2) - (height / 2), (maxX / 2) - (width / 2));
  wtimeout(menu_window, 300);
  keypad(menu_window, true);
}

void Menu::printLogo()
{
  std::string logo[] = {
      "   ####### ######  ####### #     # ",
      "      #    #     # #     # ##    # ",
      "      #    #     # #     # # #   # ",
      "      #    ######  #     # #  #  # ",
      "      #    #   #   #     # #   # # ",
      "      #    #    #  #     # #    ## ",
      "      #    #     # ####### #     # ",
  };

  for (int i = 0; i < 7; i++)
  {
    mvwaddstr(menu_window, i + 2, (width / 2) - 19, logo[i].c_str());
  }
}
