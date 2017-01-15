#ifndef APPAREO_FILES_CURSE_OUTPUT_H_
#define APPAREO_FILES_CURSE_OUTPUT_H_
#include <vector>
#include <string>
namespace appareo {
namespace curse {
namespace out {
enum Attributes {
  NORMAL = 0,
  STANDOUT = 1,
  UNDERLINE = 2,
  REVERSE = 3,
  BLINK = 4,
  DIM = 5,
  BOLD = 6,
  PROTECT = 7,
  INVIS = 8,
  ALTCHAR = 9,
  CHARTEXT = 10,
  BLACK_TEXT = 11,
  RED_TEXT = 12,
  GREEN_TEXT = 13,
  YELLOW_TEXT = 14,
  BLUE_TEXT = 15,
  MAGENTA_TEXT = 16,
  CYAN_TEXT = 17,
  WHITE_TEXT = 18,
  BLACK_BACK = 19,
  RED_BACK = 20,
  GREEN_BACK = 21,
  YELLOW_BACK = 22,
  BLUE_BACK = 23,
  MAGENTA_BACK = 24,
  CYAN_BACK = 25,
  WHITE_BACK = 26
};
extern int logloc;
extern int boundwin;
void InitializeOutput();
void PrintC(std::string str, int row = -1, int col = -1, int window = boundwin);
void Print(std::string str, int row = -1, int col = -1, int window = boundwin, bool autoupdate = true);
void PrintZ(std::string str, int zone = 1, int window = boundwin);
void NewLine(int window = boundwin);
void InitializeColor();
void SetAtt(std::vector<Attributes> attrs = {NORMAL}, int window = boundwin);
void BindWindow(int index);
void BindWindow(std::string name);
}
}
}
#endif
