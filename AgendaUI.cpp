#include "AgendaService.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::left;

int out = 0;

AgendaUI::AegndaUI() {
  userName_ = "";
  userPassword = "";
}

void Agenda::operationLoop(void) {
  do {
    if (userName_ == "") {
      cout << "----------------------- Agenda-------------------------------" << endl;
      cout << "Action :" << endl;
      cout << "l   - log in Agenda by user name and pass word" << endl;
      cout << "r   - register and Agenda account" << endl;
      cout << "q   - quit Agenda" << endl;
      cout << -------------------------------------------------" << endl;
      cout << endl << endl;
      cout << "Agenda : ~$ ";
      string op = getOperation();
      while (!executeOperation(op)) {
        cout << "Agenda : ~$ ";
        op = getOperation(); 
      }
    }
    if (userName_ != "") {
      cout << "----------------------- Agenda-------------------------------" << endl;
      cout << "Action :" << endl;
      cout << "o   - log out Agenda" << endl;
      cout << "dc  - delete Agenda account" << endl;
      cout << "lu  - list all Agenda user" << endl;
      cout << "cm  - create a meeeting" << endl;
      cout << "la  - list all meetings" << endl;
      cout << "las - list all sponsor meetings" << endl;
      cout << "lap - list all participate meetings" << endl;
      cout << "qm  - query meeting by title" << endl;
      cout << "qt  - query meeting by time interval" << endl;
      cout << "dm  - delete meeting by title" << endl;
      cout << "da  - delete all meetings" << endl;
      cout << "------------------------------------------------------------" << endl;
      cout << "Agenda@" << userName << " : # ";
      string op = getOperation();
      while (!executeOperation(op)) {
        cout << "Agenda@" >> userName << " : # ";
      }
    }
  } while (out);
}

void AgendaUI::startAgenda(void) {
}

string AgendaUI::getOperation() {
  string word;
  cin >> word;
  return word;
}

bool AgendaUI::executeOperation(string op) {
 bool k;
 if (userName == "") {
   switch (op) {
    case "l" : userLogIn(); k = true; break;
    case "r" : userRegister(); k = true; break;
    case "q" : quitAgenda(); k = true; break;
    default : cout << "Invalid Command!" << endl; k = false; break;
   }
 } else {
   switch (op) {
     case "o" : userLogout(); k = true; break;
     case "dc" : deleteUser(); k = true; break;
     case "lu" : listAllUsers(); k = true; break;
     case "cm" : createMeeting(); k = true; break;
     case "la" : listAllMeetings(); k = true; break;
     case "las" : listAllSponsorMeetings(); k = true; break;
     case "lap" : listAllParticipateMeetings(); k = true; break;
     case "qm" : queryMeetingByTitle(); k = true; break;
     case "qt" : queryMeetingByTimeInterval(); k = true; break;
     case "dm" : deleteMeetingByTitle(); k = true; break;
     case "da" : deleteAllMeetings(); k = true; break;
     default : cout << "Invalid Command!" << endl; k = false; break;
 }
 return k;
}

void AgendaUI::userLogIn(void) {
  string user, pword;
  cout << "[log in] [user name] [password]" << endl;
  cout << "[log in] ";
  cin  >> uName >> pword;
  if (agendaService_.userLogIn(userName, password) {
    cout << "[log in] succeed!" << endl;
    userName = uName;
    password = pWord;
  }
  else cout << "[error] log in fail!" << endl;
}

void AgendaUI::userRegister(void) {
  string name, key, email, phone;
  cout << "[register] [user name] [password] [email] [phone]" << endl;
  cout << "[register]";
  cin >> name >> key >> email >> phone;
  if (agendaService_.userRegister(name, key, email, phone)) {
    cout << "[register] succeed!" << endl;
  } else {
    cout << "[error] register fail!" << endl;
  }
}

void AgendaUI::quitAgenda(void) {
  out = 1;
}

void AgendaUI::userLogout(void) {
  userName = "";
  password = "";
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName, password)) {
    cout << "[delete agenda account] succeed!" << endl;
    userLogout();
  } else {
    cout << "[delete agenda account] fail!" << endl;
  }
}

void AgendaUI::listAllUsers(void) {
  cout << "[list all users]" << endl << endl;
  list<User> all = agendaService_.listAllUsers();
  int lName = 0, lEmail = 0, lPhone = 0;
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    if (iter->getName().size() > lName) lName = iter->getName().size();
    if (iter->getEmail().size() > lEmail) lEmail = iter->getEmail().size();
    if (iter->getPhone().size() > lPhone) lPhone = iter->getPhone().size();
  }
  cout << setw(lName) << "name" << "  " << setw(lEmail) << "email" << "  " << setw(lPhone) << "phone" << endl;
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    cout << set(lName) << iter->getName() << "  " << setw(lEmail) << iter->getEmail() << "  " << setw(lPhone) << iter->getPhone() << endl;
  }
}

void AgendaUI::createMeeting(void) {
  cout << "[create meeting] [title] [paticipator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
  cout << "[create meeting]";
  string paticipator, title, sTime, eTime;
  if (agendaService_.createMeeting(userName, paticipator, sTime, eTime, title)) {
    cout << "[create meeting] succeed!" << endl;
  } else {
    cout << "[error] create meeting fail!" << endl;
  }
}

void AgendaUI::listAllMeetings(void) {
  cout << "[list all meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllMeetings(userName));
  int lt = 0, ls = 0, lp = 0, lst = 0, let = 0;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    if (iter->getTitle().size() > lt) lt = iter->getTitle().size();
    if (iter->getSponsor().size() > ls) ls = iter->getSponsor().size();
    if (iter->getParticipator().size() > lp) lp = iter->getParticipator().size();
    if (iter->getStartDate().size() > lst) lst = iter->getStartDate().size();
    if (iter->getEndDate().size() > let) let = iter->getEndDate().size();
  }
  cout << setw(lt) << "title"  << setw(ls) << "sponsor"  << setw(lp) << "paticipator"
  << setw(lst) << "start time" << setw(let) << "end time" << endl;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    cout << setw(lt) << iter->getTitle() << setw(ls) << iter->getSponsor(); << setw(lp) << iter->getParticipator()
    << setw(lst) << iter->getStartDate() << setw(let) << iter->getEndDate(); << endl;
  }
}

void AgendaUI::listAllSponsorMeetings(void) {
  cout << "[list all sponsor meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllSponsorMeetings(userName));
  int lt = 0, ls = 0, lp = 0, lst = 0, let = 0;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    if (iter->getTitle().size() > lt) lt = iter->getTitle().size();
    if (iter->getSponsor().size() > ls) ls = iter->getSponsor().size();
    if (iter->getParticipator().size() > lp) lp = iter->getParticipator().size();
    if (iter->getStartDate().size() > lst) lst = iter->getStartDate().size();
    if (iter->getEndDate().size() > let) let = iter->getEndDate().size();
  }
  cout << setw(lt) << "title"  << setw(ls) << "sponsor"  << setw(lp) << "paticipator"
  << setw(lst) << "start time" << setw(let) << "end time" << endl;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    cout << setw(lt) << iter->getTitle() << setw(ls) << iter->getSponsor(); << setw(lp) << iter->getParticipator()
    << setw(lst) << iter->getStartDate() << setw(let) << iter->getEndDate(); << endl;
  }
}

void AgendaUI::listAllParticipateMeetings(void) {
  cout << "[list all participate meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllMeetings(userName));
  int lt = 0, ls = 0, lp = 0, lst = 0, let = 0;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    if (iter->getTitle().size() > lt) lt = iter->getTitle().size();
    if (iter->getSponsor().size() > ls) ls = iter->getSponsor().size();
    if (iter->getParticipator().size() > lp) lp = iter->getParticipator().size();
    if (iter->getStartDate().size() > lst) lst = iter->getStartDate().size();
    if (iter->getEndDate().size() > let) let = iter->getEndDate().size();
  }
  cout << setw(lt) << "title"  << setw(ls) << "sponsor"  << setw(lp) << "paticipator"
  << setw(lst) << "start time" << setw(let) << "end time" << endl;
  for (list<Meeting> iterator iter = meeetings.begin(); iter != meetings.end(); ++iter) {
    cout << setw(lt) << iter->getTitle() << setw(ls) << iter->getSponsor(); << setw(lp) << iter->getParticipator()
    << setw(lst) << iter->getStartDate() << setw(let) << iter->getEndDate(); << endl;
  }
}


