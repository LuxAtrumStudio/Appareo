#ifndef APPAREO_FILES_CURSE_CURSE_CORE_H_
#define APPAREO_FILES_CURSE_CURSE_CORE_H_
#include <vector>
#include "window.h"
#include "form.h"
namespace appareo {
namespace curse {
extern int logloc;
extern int scrwidth, scrheight;
extern std::vector<Window> windows;
extern Window* win;
void InitializeNcurses();
void TerminateNCurses();
void Frame();
void InitializeWindow();
void TerminateWindow(int window);
int FindWindow(std::string name);
std::vector<std::string> NewMenu(std::vector<std::string> options,
                                 std::string name = "", int width = -1,
                                 int height = -1, int posx = -1, int posy = -1,
                                 bool multi = false);
std::vector<std::string> NewMenu(std::vector<std::vector<std::string>> options,
                                 std::string name = "", int width = -1,
                                 int height = -1, int posx = -1, int posy = -1,
                                 bool multi = false);
std::vector<Field> NewForm(std::vector<Field> fields, std::string name = "",
                int width = -1, int height = -1, int posx = -1, int posy = -1);
}
}
#endif
