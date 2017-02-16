#include "curse_core.h"
#include "window.h"
#include <ncurses.h>
#include <pessum.h>
#include <string>

void appareo::curse::Window::CreateWindow(std::string winname, int winwidth,
                                          int winheight, int winposx,
                                          int winposy, bool winborder,
                                          bool wintitle) {
  windowpointer = NULL;
  if (winname == "") {
    winname = GenName();
  }
  if (winwidth == -1) {
    winwidth = scrwidth;
  }
  if (winheight == -1) {
    winheight = scrheight;
  }
  if (winposx == -1) {
    winposx = (scrwidth - winwidth) / 2;
  }
  if (winposy == -1) {
    winposy = (scrheight - winheight) / 2;
  }
  name = winname;
  width = winwidth;
  height = winheight;
  posx = winposx;
  posy = winposy;
  border = winborder;
  title = wintitle;
  cursx = 0;
  cursy = 0;
  if (border == true) {
    cursx++;
    cursy++;
  }
  logloc = pessum::logging::AddLogLocation("appareo_files/curse/window.cpp/[" +
                                           name + "]");
  windowpointer = newwin(height, width, posy, posx);
  if (windowpointer != NULL) {
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Creaded window \"" + name + "\"", logloc,
                            "CreateWindow");
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to create window \"" + name + "\"", logloc,
                            "CreateWindow");
  }
  if (border == true) {
    box(windowpointer, 0, 0);
  }
  if (title == true) {
    mvwprintw(windowpointer, 0, (width - name.size()) / 2, name.c_str());
  }
  keypad(windowpointer, TRUE);
  Update();
}

void appareo::curse::Window::TerminateWindow() {
  wclear(windowpointer);
  wrefresh(windowpointer);
  delwin(windowpointer);
  pessum::logging::LogLoc(pessum::logging::SUCCESS,
                          "Terminated window \"" + name + "\"", logloc,
                          "TerminateWindow");
}

void appareo::curse::Window::SetBackground(out::Attributes attr) {
  int color = -1;
  if (attr > 10 && attr < 19) {
    if (color == -1) {
      color++;
    }
    color += (attr - 11);
  } else if (attr > 18 && attr < 27) {
    if (color == -1) {
      color++;
    }
    color += (attr - 19) * 10;
  }
  if (color != -1) {
    wbkgd(windowpointer, COLOR_PAIR(color));
  }
}

void appareo::curse::Window::Update() {
  if (windowpointer != NULL) {
    wrefresh(windowpointer);
  }
}

void appareo::curse::Window::Clear() {
  std::string line = "";
  for (int i = 0; i < width; i++) {
    line += " ";
  }
  if (border == true) {
    line.pop_back();
    line.pop_back();
    for (int i = 1; i < height - 1; i++) {
      mvwprintw(windowpointer, i, 1, line.c_str());
    }
  } else {
    for (int i = 0; i < height; i++) {
      mvwprintw(windowpointer, i, 0, line.c_str());
    }
  }
  Update();
}

std::string appareo::curse::Window::GenName() {
  std::string name;
  std::vector<std::string> names =
      pessum::luxreader::LoadLuxListFile("resources/names.lux");
  name = names[rand() % names.size()];
  return (name);
}
