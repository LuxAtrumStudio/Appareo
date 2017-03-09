#include "curse_headers.h"
#include <ncurses.h>
#include <pessum.h>
#include <vector>

namespace appareo {
namespace curse {
int logloc;
int scrwidth, scrheight;
std::vector<Window> windows;
Window *win;
}
}

void appareo::curse::InitializeNcurses() {
  logloc =
      pessum::logging::AddLogLocation("appareo_files/curse/curse_core.cpp/");
  initscr();
  cbreak();
  keypad(stdscr, true);
  getmaxyx(stdscr, scrheight, scrwidth);
  noecho();
  curs_set(0);
  // pessum::logging::Log("s", "Initialized Ncurses", logloc,
  // "InitializeNcurses");
  out::InitializeOutput();
  out::InitializeColor();
  refresh();
}

void appareo::curse::TerminateNCurses() {
  for (int i = 0; i < windows.size(); i++) {
    windows[i].TerminateWindow();
  }
  refresh();
  endwin();
  // pessum::logging::LogLoc(pessum::logging::SUCCESS, "Terminated Ncurses",
  //                         logloc, "TerminateNCurses");
}

void appareo::curse::Frame() {
  clear();
  refresh();
  for (int i = 0; i < windows.size(); i++)
    windows[i].Update();
}

void appareo::curse::InitializeWindow() {
  Window newwindow;
  windows.push_back(newwindow);
  win = &windows[windows.size() - 1];
}

void appareo::curse::TerminateWindow(int window) {
  windows[window].TerminateWindow();
  windows.erase(windows.begin() + window);
}

int appareo::curse::FindWindow(std::string name) {
  for (int i = 0; i < windows.size(); i++) {
    if (windows[i].name == name) {
      return (i);
    }
  }
  pessum::logging::Log("w", "No window named \"" + name + "\"",
                       "appareo/curse/curse_core/", "FindWindow");
  return (0);
}

std::vector<std::string>
appareo::curse::NewMenu(std::vector<std::string> options, std::string name,
                        int width, int height, int posx, int posy, bool multi) {
  std::vector<std::string> output;
  Menu newmenu;
  newmenu.CreateMenu(options, name, width, height, posx, posy, multi);
  output = newmenu.RunMenu();
  newmenu.TerminateMenu();
  return (output);
}

std::vector<std::string>
appareo::curse::NewMenu(std::vector<std::vector<std::string>> options,
                        std::string name, int width, int height, int posx,
                        int posy, bool multi) {
  std::vector<std::string> output;
  Menu newmenu;
  newmenu.CreateMenu(options, name, width, height, posx, posy, multi);
  output = newmenu.RunMenu();
  newmenu.TerminateMenu();
  return (output);
}

std::vector<appareo::curse::Field>
appareo::curse::NewForm(std::vector<Field> fields, std::string name, int width,
                        int height, int posx, int posy) {
  Form newform;
  newform.CreateForm(fields, name, width, height, posx, posy);
  fields = newform.RunForm();
  newform.TerminateForm();
  return (fields);
}
