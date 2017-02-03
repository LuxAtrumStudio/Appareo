#include "appareo_core.h"
#include "curse/curse_core.h"
#include <pessum.h>

void appareo::InitializeAppareo(bool devmode) {
  srand(time(NULL));
  pessum::InitializePessumComponents(devmode);
  curse::InitializeNcurses();
}

void appareo::TerminateAppareo() {
  curse::TerminateNCurses();
  pessum::TerminatePessumComponents();
}
