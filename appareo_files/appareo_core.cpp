#include "appareo_core.h"
#include <pessum_headers.h>

void appareo::InitializeAppareo(){
  pessum::InitializePessumComponents();
}

void appareo::TerminateAppareo(){
  pessum::TerminatePessumComponents();
}
