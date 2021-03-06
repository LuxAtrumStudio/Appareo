#ifndef APPAREO_FILES_CURSE_FORM_H_
#define APPAREO_FILES_CURSE_FORM_H_
#include "window.h"
#include <ncurses.h>
#include <string>
#include <vector>
namespace appareo {
namespace curse {
struct Field {
  std::string name;
  int type;
  int ival;
  double dval;
  bool bval;
  std::string sval;
  std::vector<std::string> options;
};
class Form {
public:
  void CreateForm(std::vector<Field> fields, std::string name = "",
                  int width = -1, int height = -1, int posx = -1,
                  int posy = -1);
  std::vector<Field> RunForm();
  void TerminateForm();

private:
  int currentfield, max, curs;
  std::string name;
  std::vector<Field> formfields;
  Window formwin;
  void Update();
  void PrintField(int index);
  bool CharCheck(int in, int type);
};
}
}
#endif
