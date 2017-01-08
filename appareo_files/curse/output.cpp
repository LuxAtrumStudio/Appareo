#include <ncurses.h>
#include <pessum_headers.h>
#include <string>
#include <vector>
#include "curse_core.h"
#include "output.h"
#include "window.h"

namespace appareo {
namespace curse {
namespace out {
int logloc;
int boundwin;
}
}
}

void appareo::curse::out::InitializeOutput() {
  boundwin = 0;
  logloc = pessum::logging::AddLogLocation("appareo_files/curse/output.cpp/");
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized output",
                          logloc, "InitializeOutput");
}

void appareo::curse::out::PrintC(std::string str, int row, int col,
                                 int window) {
  if (row == -1) {
    row = windows[window].cursy;
  }
  if (col == -1) {
    col = windows[window].cursx;
    windows[window].cursx += str.size();
  }
  for (int i = 0; i < str.size(); i++) {
    mvwaddch(windows[window].windowpointer, row, col, str[i]);
    col++;
  }
}

void appareo::curse::out::Print(std::string str, int row, int col, int window) {
  if (row == -1) {
    row = windows[window].cursy;
  }
  if (col == -1) {
    col = windows[window].cursx;
    windows[window].cursx += str.size();
  }
  if (mvwprintw(windows[window].windowpointer, row, col, str.c_str()) == ERR) {
    pessum::logging::LogLoc(pessum::logging::WARNING, "Failed to print string",
                            logloc, "Print");
  }
  windows[window].Update();
}
void appareo::curse::out::PrintZ(std::string str, int zone, int window) {
  int length = str.size(), width = windows[window].width,
      height = windows[window].height;
  bool border = windows[window].border;
  int row = 0, col = 0;
  if(zone == 1 || zone == 2 || zone == 3){
    row = 0;
    if(border == true){
      row++;
    }
  }
  if(zone == 4 || zone == 5||zone == 6){
    row = height / 2;
  }
  if(zone == 7 || zone == 8 || zone == 9){
    row = height;
    if(border == true){
      row-=2;
    }
  }
  if(zone == 1 | zone == 4 || zone == 7){
    col = 0;
    if(border == true){
      col++;
    }
  }
  if(zone == 2 || zone == 5 || zone == 8){
    col = (width - length) / 2;
  }
  if(zone== 3 || zone == 6 || zone == 9){
    col = width - length;
    if(border == true){
      col--;
    }
  }
  Print(str, row, col, window);
}

void appareo::curse::out::InitializeColor() {
  if (has_colors() == false) {
    pessum::logging::LogLoc(pessum::logging::WARNING,
                            "Your console does not support colors", logloc,
                            "InitializeColor");
  } else {
    if (can_change_color() == false) {
      pessum::logging::LogLoc(pessum::logging::WARNING,
                              "Your console does not support costom colors",
                              logloc, "InitializeColor");
    }
    start_color();
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        init_pair((short)(i * 10 + j), (short)j, (short)i);
      }
    }
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized colors",
                            logloc, "InitializeColor");
  }
}

void appareo::curse::out::SetAtt(std::vector<Attributes> attrs) {
  wattrset(windows[boundwin].windowpointer, A_NORMAL);
  int color = -1;
  for (int i = 0; i < attrs.size(); i++) {
    if (attrs[i] > 10 && attrs[i] < 19) {
      if (color == -1) {
        color++;
      }
      color += (attrs[i] - 11);
    } else if (attrs[i] > 18 && attrs[i] < 27) {
      if (color == -1) {
        color++;
      }
      color += (attrs[i] - 19) * 10;
    } else if (attrs[i] == 0) {
      wattron(windows[boundwin].windowpointer, A_NORMAL);
    } else if (attrs[i] == 1) {
      wattron(windows[boundwin].windowpointer, A_STANDOUT);
    } else if (attrs[i] == 2) {
      wattron(windows[boundwin].windowpointer, A_UNDERLINE);
    } else if (attrs[i] == 3) {
      wattron(windows[boundwin].windowpointer, A_REVERSE);
    } else if (attrs[i] == 4) {
      wattron(windows[boundwin].windowpointer, A_BLINK);
    } else if (attrs[i] == 5) {
      wattron(windows[boundwin].windowpointer, A_DIM);
    } else if (attrs[i] == 6) {
      wattron(windows[boundwin].windowpointer, A_BOLD);
    } else if (attrs[i] == 7) {
      wattron(windows[boundwin].windowpointer, A_PROTECT);
    } else if (attrs[i] == 8) {
      wattron(windows[boundwin].windowpointer, A_INVIS);
    } else if (attrs[i] == 9) {
      wattron(windows[boundwin].windowpointer, A_ALTCHARSET);
    } else if (attrs[i] == 10) {
      wattron(windows[boundwin].windowpointer, A_CHARTEXT);
    }
  }
  if (color != -1) {
    wattron(windows[boundwin].windowpointer, COLOR_PAIR(color));
  }
  refresh();
}

void appareo::curse::out::BindWindow(int index) { boundwin = index; }

void appareo::curse::out::BindWindow(std::string name) {
  boundwin = appareo::curse::FindWindow(name);
}
