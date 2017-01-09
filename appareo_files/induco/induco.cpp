#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../curse/curse_headers.h"
#include "induco.h"
namespace appareo {
namespace induco {
struct termios t;
clock_t start;
int barwin = 0, lastbar = 0;
}
}

void appareo::induco::CreateProgressBar(std::string name) {
  curse::InitializeWindow();
  curse::win->CreateWindow(name, curse::scrwidth / 2, 3, -1, -1, true, true);
  barwin = curse::windows.size() - 1;
  lastbar = -1;
}

void appareo::induco::UpdateProgressBar(double percent) {
  std::string bar = "";
  percent *= 100;
  double worth = 100.0 / (double)(curse::windows[barwin].width - 2);
  for (int i = 0; i * worth < percent; i++) {
    bar += " ";
  }
  if (lastbar != bar.size()) {
    std::string perc = std::to_string(percent);
    int col = (curse::windows[barwin].width - perc.size()) / 2;
    lastbar = bar.size();
    curse::out::SetAtt({curse::out::WHITE_BACK}, barwin);
    curse::out::Print(bar, 1, 1, barwin);
    for(int i = 0; i < perc.size(); i++){
      if(col > bar.size() + 1){
      curse::out::SetAtt({curse::out::NORMAL}, barwin);
      }
      std::stringstream ss;
      ss << perc[i];
      std::string sch;
      ss >> sch;
      curse::out::Print(sch, 1, col, barwin);
      col++;
    }
  }
}

void appareo::induco::TerminateProgressBar() {
  curse::windows[barwin].TerminateWindow();
  curse::windows.erase(curse::windows.begin() + barwin);
}

std::string appareo::induco::DisplayTime(double elapsed, bool unit) {
  std::string line = "", hstring, minstring, secstring, msstring, usstring;
  int microsec = 0, millisec = 0, sec = 0, min = 0, hour = 0;
  sec = floor(elapsed);
  elapsed -= sec;
  elapsed = elapsed * 1000;
  millisec = floor(elapsed);
  elapsed -= millisec;
  elapsed = elapsed * 1000;
  microsec = round(elapsed);
  while (sec >= 60) {
    sec -= 60;
    min++;
  }
  while (min >= 60) {
    min -= 60;
    hour++;
  }
  hstring = std::to_string(hour);
  line = line + hstring;
  if (unit == true) {
    line = line + "h";
  }
  for (int j = hstring.size(); j < 6; j++) {
    line = line + " ";
  }
  line = line + "|";
  minstring = std::to_string(min);
  line = line + minstring;
  if (unit == true) {
    line = line + "m";
  }
  for (int j = minstring.size(); j < 5; j++) {
    line = line + " ";
  }
  line = line + "|";
  secstring = std::to_string(sec);
  line = line + secstring;
  if (unit == true) {
    line = line + "s";
  }
  for (int j = secstring.size(); j < 5; j++) {
    line = line + " ";
  }
  line = line + "|";
  msstring = std::to_string(millisec);
  line = line + msstring;
  if (unit == true) {
    line = line + "ms";
  }
  for (int j = msstring.size(); j < 4; j++) {
    line = line + " ";
  }
  line = line + "|";
  usstring = std::to_string(microsec);
  line = line + usstring;
  if (unit == true) {
    line = line + "us";
  }
  for (int j = usstring.size(); j < 4; j++) {
    line = line + " ";
  }
  return (line);
}

std::string appareo::induco::DisplayDate(int timesec, bool disptime,
                                         bool dispyear) {
  time_t duedate = timesec;
  std::string duedatestr = "";
  duedatestr = ctime(&duedate);
  duedatestr.pop_back();
  if (dispyear == false) {
    duedatestr.erase(duedatestr.end() - 5, duedatestr.end());
  }
  if (disptime == false) {
    duedatestr.erase(duedatestr.begin() + 10, duedatestr.begin() + 19);
  }
  return (duedatestr);
}

double appareo::induco::Timer(bool startb) {
  if (startb == true) {
    start = clock();
  } else if (startb == false) {
    clock_t end = clock();
    double elapsedtime = (end - start) / (double)CLOCKS_PER_SEC;
    return (elapsedtime);
  }
  return (0);
}
