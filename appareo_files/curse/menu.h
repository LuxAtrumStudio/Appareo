#ifndef APPAREO_FILES_CURSE_MENU_H_
#define APPAREO_FILES_CURSE_MENU_H_
#include <string>
#include <vector>
#include "window.h";
namespace appareo {
namespace curse {
class Menu {
 public:
  void CreateMenu(std::vector<std::string> options, std::string name = "",
                  int width = -1, int height = -1, int posx = -1, int posy = -1,
                  bool multi = false);
  void CreateMenu(std::vector<std::vector<std::string>> options,
                  std::string name = "", int width = -1, int height = -1,
                  int posx = -1, int posy = -1, bool multi = false);
  std::vector<std::string> RunMenu();
  void TerminateMenu();

 private:
  std::vector<std::vector<std::string>> menuoptions;
  std::vector<std::vector<bool>> selectcheck;
  std::vector<std::string> selections;
  int currentcol, currentrow;
  bool multiselect;
  Window menuwin;
  void Update();
};
}
}
#endif
