#ifndef APPAREO_FILES_CURSE_WINDOW_H_
#define APPAREO_FILES_CURSE_WINDOW_H_
#include "output.h"
#include <ncurses.h>
#include <string>
namespace appareo {
namespace curse {
class Window {
public:
  std::string name;
  WINDOW *windowpointer;
  int cursx, cursy;
  int width, height, posx, posy;
  bool title, border;
  void CreateWindow(std::string winname = "", int winwidth = -1,
                    int winheight = -1, int winposx = -1, int winposy = -1,
                    bool winborder = true, bool wintitle = false);
  void TerminateWindow();
  void SetBackground(out::Attributes attr = out::NORMAL);
  void Update();
  void Clear();

private:
  std::string GenName();
};
}
}
#endif
