#include "Meeting.h"
#include "Date.h"
#include "Storage.h"
#include "User.h"
#include "AgendaService.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

int main() {
  AgendaService agenda;
  agenda.startAgenda();
  if (agenda.userRegister("William", "17881243", "williamjwking@gmail.com", "8130770")) cout << "Regist sucessfully!" << endl;
  string userName, password;
  cout << "name:" << endl;
  cin >> userName;
  cout << "password:" << endl;
  cin >> password;
  if (agenda.userLogIn(userName, password)) cout << "Login sucessfully!" << endl;
  if (agenda.deleteUser(userName, password)) cout << "Logout successfully!" << endl;
  if (agenda.createMeeting("William", "Love", "Smartmoon", "2014-11-02/08:40", "2014-11-02/24:00")) cout << "Create successfully!" << endl;
  else cout << "??" << endl;
  if (agenda.createMeeting("William", "Love1", "Smartmoon", "2014-11-02/08:40", "2014-11-02/24:00")) cout << "Create successfully!" << endl;
  else cout << "Have no time" << endl;
  if (agenda.createMeeting("William", "Love2", "Smartmoon", "2014-11-03/08:40", "2014-11-02/24:00")) cout << "Create successfully!" << endl;
  else cout << "Time < 0" << endl;
  if (agenda.createMeeting("William", "Love", "Smartmoon", "2014-11-03/08:40", "2014-11-03/24:00")) cout << "Create successfully!" << endl;
  else cout << "Repeat name" << endl;
  if (agenda.createMeeting("William", "Love", "Smartmoon", "2014-11-99/08:40", "2014-11-02/24:00")) cout << "Create successfully!" << endl;
  else cout << "Invalid Time" << endl;
  agenda.quitAgenda();
}
