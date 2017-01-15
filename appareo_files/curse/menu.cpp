#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>
#include <pessum.h>
#include "curse_headers.h"

void appareo::curse::Menu::CreateMenu(std::vector<std::string> options,
                                      std::string name, int width, int height,
                                      int posx, int posy, bool multi) {
  for (int i = 0; i < options.size(); i++) {
    menuoptions.push_back({options[i]});
  }
  multiselect = multi;
  menuwin.CreateWindow(name, width, height, posx, posy, true, true);

  if (multi == true) {
    mvwprintw(menuwin.windowpointer, menuwin.height - 1,
              (menuwin.width - 4) / 2, "<OK>");
  }
  for (int i = 0; i < menuoptions.size(); i++) {
    std::vector<bool> colcheck;
    for (int j = 0; j < menuoptions[i].size(); j++) {
      colcheck.push_back(false);
    }
    selectcheck.push_back(colcheck);
  }
  Update();
  refresh();
}

void appareo::curse::Menu::CreateMenu(
    std::vector<std::vector<std::string>> options, std::string name, int width,
    int height, int posx, int posy, bool multi) {
  menuoptions = options;
  multiselect = multi;
  menuwin.CreateWindow(name, width, height, posx, posy, true, true);
  if (multi == true) {
    mvwprintw(menuwin.windowpointer, menuwin.height - 1,
              (menuwin.width - 4) / 2, "<OK>");
  }

  for (int i = 0; i < menuoptions.size(); i++) {
    std::vector<bool> colcheck;
    for (int j = 0; j < menuoptions[i].size(); j++) {
      colcheck.push_back(false);
    }
    selectcheck.push_back(colcheck);
  }
  Update();
  refresh();
}

std::vector<std::string> appareo::curse::Menu::RunMenu() {
  bool running = true;
  currentcol = 0;
  currentrow = 0;
  while (running == true) {
    Update();
    int input = wgetch(menuwin.windowpointer);
    if (input == KEY_UP && currentrow > 0) {
      currentrow--;
      if(currentcol >= menuoptions[currentrow].size()){
        currentcol = menuoptions[currentrow].size() - 1;
      }
    }
    if (input == KEY_DOWN && currentrow < menuoptions.size() - 1) {
      currentrow++;
      if(currentcol >= menuoptions[currentrow].size()){
        currentcol = menuoptions[currentrow].size() - 1;
      }
    } else if (input == KEY_DOWN && currentrow == menuoptions.size() - 1 &&
               multiselect == true) {
      currentrow++;
      if(currentcol >= menuoptions[currentrow].size()){
        currentcol = menuoptions[currentrow].size() - 1;
      }
    }
    if (input == KEY_LEFT && currentcol > 0) {
      currentcol--;
    }
    if (input == KEY_RIGHT && currentcol < menuoptions[currentrow].size() - 1) {
      currentcol++;
    }
    if (input == 10) {
      if (multiselect == false) {
        selections.push_back(menuoptions[currentrow][currentcol]);
        running = false;
      } else if (multiselect == true) {
        if (currentrow == menuoptions.size()) {
          running = false;
        } else {
          if (selectcheck[currentrow][currentcol] == false) {
            selectcheck[currentrow][currentcol] = true;
            selections.push_back(menuoptions[currentrow][currentcol]);
          } else if (selectcheck[currentrow][currentcol] == true) {
            selectcheck[currentrow][currentcol] = false;
            for(int i = 0 ; i < selections.size(); i++){
              if(selections[i] == menuoptions[currentrow][currentcol]){
                selections.erase(selections.begin() + i);
              }
            }
          }
        }
      }
    }
  }
  return (selections);
}

void appareo::curse::Menu::TerminateMenu() {
  menuoptions.clear();
  selections.clear();
  menuwin.TerminateWindow();
}

void appareo::curse::Menu::Update() {
  int width = menuwin.width - 2, height = menuwin.height - 2;
  for (int i = 0; i < menuoptions.size(); i++) {
    for (int j = 0; j < menuoptions[i].size(); j++) {
      if (i == currentrow && j == currentcol) {
        wattron(menuwin.windowpointer, COLOR_PAIR(70));
      }
      if (selectcheck[i][j] == true) {
        wattron(menuwin.windowpointer, A_BOLD);
      }
      int posx, posy;
      posy = (i * (height / menuoptions.size())) +
             (((height / menuoptions.size()) - 1) / 2);
      posx = (j * (width / menuoptions[i].size())) +
             (((width / menuoptions[i].size()) - menuoptions[i][j].size()) / 2);
      mvwprintw(menuwin.windowpointer, posy, posx, menuoptions[i][j].c_str());
      if (selectcheck[i][j] == true) {
        wattroff(menuwin.windowpointer, A_BOLD);
      }
      if (i == currentrow && j == currentcol) {
        wattroff(menuwin.windowpointer, COLOR_PAIR(70));
      }
    }
  }
  if (multiselect == true) {
    if (currentrow == menuoptions.size()) {
      wattron(menuwin.windowpointer, COLOR_PAIR(70));
    }
    mvwprintw(menuwin.windowpointer, menuwin.height - 1,
              (menuwin.width - 4) / 2, "<OK>");
    if (currentrow == menuoptions.size()) {
      wattroff(menuwin.windowpointer, COLOR_PAIR(70));
    }
  }
  menuwin.Update();
}
