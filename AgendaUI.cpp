#include "AgendaService.h"

AgendaUI::AegndaUI() {
  userName_ = "";
  userPassword = "";
}

void Agenda::operationLoop(void) {
  if (userName_ == "") {
    cout << "--------------------Agenda-------------------" << endl;
    cout << "Action :"
    cout << "l   - log in Agenda by user name and pass word" << endl;
    cout << "r   - register and Agenda account" << endl;
    cout << "q   - quit Agenda" << endl;
  }
  

void Agenda::startAgenda(void) {
  operationLoop();
}


