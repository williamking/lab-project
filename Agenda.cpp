#include "AgendaUI.h"

AgendaUI aui;

int main(int argc,char *argv[]) {
  char *name = argv[2];
  aui.OperationLoop(name);
  return 0;
}
