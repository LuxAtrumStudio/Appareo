#include "curse_headers.h"
#include "form.h"
#include <ncurses.h>
#include <pessum.h>
#include <sstream>
#include <string>
#include <vector>

void appareo::curse::Form::CreateForm(std::vector<Field> fields,
                                      std::string name, int width, int height,
                                      int posx, int posy) {
  formfields = fields;
  formwin.CreateWindow(name, width, height, posx, posy, true, true);
  max = 0;
  for (int i = 0; i < formfields.size(); i++) {
    if (max < formfields[i].name.size()) {
      max = formfields[i].name.size();
    }
  }
  for (int i = 0; i < formfields.size(); i++) {
    PrintField(i);
  }
  mvwprintw(formwin.windowpointer, formwin.height - 1, (formwin.width - 4) / 2,
            "<OK>");
  refresh();
}

std::vector<appareo::curse::Field> appareo::curse::Form::RunForm() {
  bool running = true;
  currentfield = 0;
  curs = formfields[currentfield].sval.size();
  while (running == true) {
    Update();
    int input = 0;
    input = wgetch(formwin.windowpointer);
    if (input == 10 && formfields[currentfield].type == 6) {
      formfields[currentfield].sval = NewMenu(
          formfields[currentfield].options, formfields[currentfield].name,
          formwin.width - 2, formwin.height - 2, formwin.posx + 1,
          formwin.posy + 1, false)[0];
      for (int i = 0; i < formfields[currentfield].options.size(); i++) {
        if (formfields[currentfield].sval ==
            formfields[currentfield].options[i]) {
          formfields[currentfield].ival = i;
          break;
        }
      }
      formwin.Update();
    }
    if (input == KEY_UP) {
      if (currentfield > 0) {
        currentfield--;
        if (currentfield < formfields.size()) {
          curs = formfields[currentfield].sval.size();
        }
      }
    }
    if (input == KEY_DOWN || input == 10) {
      if (currentfield < formfields.size()) {
        currentfield++;
        if (currentfield < formfields.size()) {
          curs = formfields[currentfield].sval.size();
        }
      }
    }
    if (currentfield < formfields.size()) {
      if (input == KEY_RIGHT) {
        if (curs < formfields[currentfield].sval.size()) {
          curs++;
        }
        if (formfields[currentfield].type == 3 &&
            formfields[currentfield].bval == false) {
          formfields[currentfield].bval = true;
        }
      }
      if (input == KEY_LEFT) {
        if (curs > 0) {
          curs--;
        }
        if (formfields[currentfield].type == 3 &&
            formfields[currentfield].bval == true) {
          formfields[currentfield].bval = false;
        }
      }
      if (input == KEY_BACKSPACE) {
        if (curs > 0 && formfields[currentfield].sval.size() >= curs) {
          formfields[currentfield].sval.erase(
              formfields[currentfield].sval.begin() + curs - 1);
          curs--;
          if (curs < 0) {
            curs = 0;
          }
        }
      }
      if (CharCheck(input, formfields[currentfield].type) == true) {
        char ch = char(input);
        formfields[currentfield].sval.insert(
            formfields[currentfield].sval.begin() + curs, ch);
        curs++;
      }
    } else if (currentfield == formfields.size()) {
      if (input == 10) {
        running = false;
      }
    }
  }
  for (int i = 0; i < formfields.size(); i++) {
    if ((formfields[i].type == 1 || formfields[i].type == 2) &&
        formfields[i].sval == "") {
      formfields[i].sval = "0";
    }
    if (formfields[i].type == 1) {
      formfields[i].ival = stoi(formfields[i].sval);
    } else if (formfields[i].type == 2) {
      formfields[i].dval = stod(formfields[i].sval);
    }
  }
  return (formfields);
}

void appareo::curse::Form::TerminateForm() {
  formfields.clear();
  formwin.TerminateWindow();
}

void appareo::curse::Form::Update() {
  for (int i = 0; i < formfields.size(); i++) {
    PrintField(i);
  }
  if (currentfield == formfields.size()) {
    wattron(formwin.windowpointer, A_STANDOUT);
  }
  mvwprintw(formwin.windowpointer, formwin.height - 1, (formwin.width - 4) / 2,
            "<OK>");
  if (currentfield == formfields.size()) {
    wattroff(formwin.windowpointer, A_STANDOUT);
  }
  formwin.Update();
}

void appareo::curse::Form::PrintField(int index) {
  std::string value;
  value = formfields[index].sval;
  if (formfields[index].type == 5) {
    for (int i = 0; i < value.size(); i++) {
      value[i] = '*';
    }
  }
  while (value.size() + max + 4 < formwin.width - 2) {
    value += " ";
  }
  mvwprintw(formwin.windowpointer, index + 1, 2,
            (formfields[index].name + ":").c_str());

  if (formfields[index].type != 3) {
    if (currentfield == index) {
      wattron(formwin.windowpointer, COLOR_PAIR(70));
    }
    for (int i = 0; i < value.size(); i++) {
      if (i == curs && index == currentfield) {
        wattron(formwin.windowpointer, A_BOLD);
      }
      std::stringstream ss;
      ss << value[i];
      std::string sch;
      ss >> sch;
      if (value[i] == ' ') {
        sch = " ";
      }
      mvwprintw(formwin.windowpointer, index + 1, max + 4 + i, sch.c_str());
      if (i == curs && index == currentfield) {
        wattroff(formwin.windowpointer, A_BOLD);
      }
    }
    if (currentfield == index) {
      wattroff(formwin.windowpointer, COLOR_PAIR(70));
    }
  } else if (formfields[index].type == 3) {
    if (formfields[index].bval == false) {
      wattron(formwin.windowpointer, COLOR_PAIR(70));
    }
    mvwprintw(formwin.windowpointer, index + 1, max + (value.size() / 3),
              "False");
    if (formfields[index].bval == false) {
      wattroff(formwin.windowpointer, COLOR_PAIR(70));
    }
    if (formfields[index].bval == true) {
      wattron(formwin.windowpointer, COLOR_PAIR(70));
    }
    mvwprintw(formwin.windowpointer, index + 1, max + 5 * (value.size() / 6),
              "True");
    if (formfields[index].bval == true) {
      wattroff(formwin.windowpointer, COLOR_PAIR(70));
    }
  }
}

bool appareo::curse::Form::CharCheck(int in, int type) {
  if (type == 1 && ((in >= 48 && in <= 57) || in == 45)) {
    return (true);
  } else if (type == 2 && ((in >= 48 && in <= 57) || in == 46 || in == 45)) {
    return (true);
  } else if ((type == 4 || type == 5) && in >= 32 && in <= 126) {
    return (true);
  }
  return (false);
}
