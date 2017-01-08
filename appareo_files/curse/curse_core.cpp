#include <ncurses.h>
#include <pessum_headers.h>
#include <vector>
#include "curse_core.h"
#include "output.h"
#include "window.h"

namespace appareo {
namespace curse {
int logloc;
int scrwidth, scrheight;
std::vector<Window> windows;
Window* win;
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
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized Ncurses",
                          logloc, "InitializeNcurses");
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
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Terminated Ncurses",
                          logloc, "TerminateNCurses");
}

void appareo::curse::Frame() {
  clear();
  refresh();
  for (int i = 0; i < windows.size(); i++) windows[i].Update();
}

void appareo::curse::InitializeWindow() {
  Window newwindow;
  windows.push_back(newwindow);
  out::BindWindow(windows.size() - 1);
  win = &windows[windows.size() - 1];
}

int appareo::curse::FindWindow(std::string name) {
  for (int i = 0; i < windows.size(); i++) {
    if (windows[i].name == name) {
      return (i);
    }
  }
  pessum::logging::LogLoc(pessum::logging::WARNING,
                          "No window named \"" + name + "\"", logloc,
                          "FindWindow");
  return (0);
}
