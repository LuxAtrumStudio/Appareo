#ifndef APPAREO_FILES_CURSE_CURSE_CORE_H_
#define APPAREO_FILES_CURSE_CURSE_CORE_H_
#include <vector>
#include "window.h"
namespace appareo{
  namespace curse{
    extern int logloc;
    extern int scrwidth, scrheight;
    extern std::vector<Window> windows;
    extern Window* win;
    void InitializeNcurses();
    void TerminateNCurses();
    void Frame();
    void InitializeWindow();
    int FindWindow(std::string name);
  }
}
#endif
