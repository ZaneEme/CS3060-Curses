#include <ncurses.h>
#include <menu.h>
// Base class, everything extends
class Menu {
 private:
  WINDOW *menu_window;
  std::vector<struct MenuEntry> items;
  int selected_index;

  struct MenuEntry {
    std::string text;
    int value;
  };

 public:
  Menu(int x, int y, int width, int height) {
    // Initialize ncurses.
    initscr();
    cbreak();
    noecho();

    // Create the menu window.
    menu_window = newwin(height, width, y, x);
    box(menu_window, 0, 0);

    // Add menu items.
    for (int i = 0; i < items.size(); i++) {
      mvwaddstr(menu_window, i + 1, 1, items[i].text.c_str());
    }

    // Show the menu.
    wrefresh(menu_window);
  }

  ~Menu() {
    // Clean up.
    delwin(menu_window);
    endwin();
  }

  // Add a menu item.
  void AddItem(std::string text) {
    items.push_back({text, -1});
  }

  // Set the selected item.
  void SetSelectedIndex(int index) {
    selected_index = index;
  }

  // Get the selected item.
  std::string GetSelectedItem() {
    return items[selected_index].text;
  }

  // Get the user's choice.
  int GetChoice() {
    // Get the user's input.
    int key = wgetch(menu_window);

    // If the user pressed an arrow key, move the selection.
    if (key == KEY_UP) {
      if (selected_index > 0) {
        selected_index--;
      }
    } else if (key == KEY_DOWN) {
      if (selected_index < items.size() - 1) {
        selected_index++;
      }
    } else if (key == KEY_ENTER) {
      // The user has selected an item.
      return selected_index;
    }

    // Refresh the menu.
    wrefresh(menu_window);

    // Keep looping until the user presses enter.
    return -1;
  }
};