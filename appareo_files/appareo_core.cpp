#include <pessum_headers.h>
#include "appareo_core.h"
#include "curse/curse_core.h"

void appareo::InitializeAppareo() {
  srand(time(NULL));
  pessum::InitializePessumComponents();
  curse::InitializeNcurses();
}

void appareo::TerminateAppareo() {
  curse::TerminateNCurses();
  pessum::TerminatePessumComponents();
}
