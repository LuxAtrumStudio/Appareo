#ifndef INDUCO_H_
#define INDUCO_H_
#include "../curse/curse_headers.h"
#include <string>
#include <termios.h>
#include <vector>
namespace appareo {
namespace induco {
// Used to remove terminal echo of key press
extern struct termios t;
// Start time for timer
extern clock_t start;
extern int barwin, lastbar;
void CreateProgressBar(std::string name);
void UpdateProgressBar(double percent);
void TerminateProgressBar();
// Converts elapsed time double to units of h, m, s, ms, us
std::string DisplayTime(double elapsed = 0, bool unit = false);
// Converts time in s to DATE
std::string DisplayDate(int timesec, bool disptime = false,
                        bool dispyear = false);
// Starts or stops a timmer with accuracy to us
double Timer(bool startb = false);

void Line(int pos, bool vertical);
}
}
#endif
