#include "AgendaUI.h"

AgendaUI aui;

int main(argc, argv[]) {
  char *name = argv[2];
  aui.OperationLoop(name);
  return 0;
}
