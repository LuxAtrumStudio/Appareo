#include <ncurses.h>
#include <pessum_headers.h>
#include "appareo_files/appareo_core.h"
#include "appareo_files/appareo_headers.h"
using namespace appareo::curse::out;

int main() {
  appareo::InitializeAppareo();
  appareo::TerminateAppareo();
  return (1);
}
