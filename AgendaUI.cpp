#include "AgendaService.h"
#include "AgendaUI.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::left;

int out = 1;

AgendaUI::AgendaUI() {
  userName_ = "";
  userPassword_ = "";
}

void AgendaUI::OperationLoop(void) {
  do {
    if (userName_ == "") {
      cout << "----------------------- Agenda-------------------------------" << endl;
      cout << "Action :" << endl;
      cout << "l   - log in Agenda by user name and pass word" << endl;
      cout << "r   - register and Agenda account" << endl;
      cout << "q   - quit Agenda" << endl;
      cout << "-------------------------------------------------------------" << endl;
      cout << endl << endl;
      cout << "Agenda : ~$ ";
      string op = getOperation();
      executeOperation(op);
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
      cout << "-------------------------------------------------------------" << endl;
      cout << "Agenda@" << userName_ << " : # ";
      string op = getOperation();
      executeOperation(op);
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
 if (userName_ == "") {
    if (op == string("l")) { userLogIn(); k = true; } else
    if (op == string("r")) { userRegister(); k = true; } else
    if (op == string("q")) { quitAgenda(); k = true; } else
    cout << "Invalid Command!" << endl; k = false;
 } else {
     if (op == string("o")) { userLogOut(); k = true; } else
     if (op == string("dc")) { deleteUser(); k = true; } else 
     if (op == string("lu")) { listAllUsers(); k = true; } else
     if (op == string("cm")) { createMeeting(); k = true; } else
     if (op == string("la")) { listAllMeetings(); k = true; } else
     if (op == string("las")) { listAllSponsorMeetings(); k = true; } else 
     if (op == string("lap")) { listAllParticipateMeetings(); k = true; } else 
     if (op == string("qm")) { queryMeetingByTitle(); k = true; } else 
     if (op == string("qt")) { queryMeetingByTimeInterval(); k = true; } else 
     if (op == string("dm")) { deleteMeetingByTitle(); k = true; } else
     if (op == string("da")) { deleteAllMeetings(); k = true; } else
       cout << "Invalid Command!" << endl; k = false;}
     return k;
}

void AgendaUI::userLogIn(void) {
  string uName, pWord;
  cout << "[log in] [user name] [password]" << endl;
  cout << "[log in] ";
  cin  >> uName >> pWord;
  if (agendaService_.userLogIn(uName, pWord)) {
    cout << "[log in] succeed!" << endl;
    userName_ = uName;
    userPassword_ = pWord;
  }
  else cout << "[error] log in fail!" << endl;
}

void AgendaUI::userRegister(void) {
  string name, key, email, phone;
  cout << "[register] [user name] [password] [email] [phone]" << endl;
  cout << "[register] ";
  cin >> name >> key >> email >> phone;
  if (agendaService_.userRegister(name, key, email, phone)) {
    cout << "[register] succeed!" << endl;
  } else {
    cout << "[error] register fail!" << endl;
  }
}

void AgendaUI::quitAgenda(void) {
  out = 0;
}

void AgendaUI::userLogOut(void) {
  userName_ = "";
  userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    cout << "[delete agenda account] succeed!" << endl;
    userLogOut();
  } else {
    cout << "[delete agenda account] fail!" << endl;
  }
}

void AgendaUI::listAllUsers(void) {
  cout << "[list all users]" << endl << endl;
  list<User> all = agendaService_.listAllUsers();
  int lName = 4, lEmail = 4, lPhone = 5;
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    if (iter->getName().size() > lName) lName = iter->getName().size();
    if (iter->getEmail().size() > lEmail) lEmail = iter->getEmail().size();
    if (iter->getPhone().size() > lPhone) lPhone = iter->getPhone().size();
  }
  cout << left;
  cout << setw(lName) << "name" << "  " << setw(lEmail) << "email" << "  " << setw(lPhone) << "phone" << endl;
  cout << left;
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    cout << setw(lName) << iter->getName() << "  " << setw(lEmail) << iter->getEmail() << "  " << setw(lPhone) << iter->getPhone() << endl;
  }
}

void AgendaUI::createMeeting(void) {
  cout << "[create meeting] [title] [paticipator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
  cout << "[create meeting] ";
  string paticipator, title, sTime, eTime;
  cin >> title >> paticipator >> sTime >> eTime;
  if (agendaService_.createMeeting(userName_, title, paticipator, sTime, eTime)) {
    cout << "[create meeting] succeed!" << endl;
  } else {
    cout << "[error] create meeting fail!" << endl;
  }
}

void AgendaUI::listAllMeetings(void) {
  cout << "[list all meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllMeetings(userName_);
  printMeetings(meetings);
}

void AgendaUI::listAllSponsorMeetings(void) {
  cout << "[list all sponsor meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllSponsorMeetings(userName_);
  printMeetings(meetings);
}

void AgendaUI::listAllParticipateMeetings(void) {
  cout << "[list all participate meetings]" << endl << endl;
  list<Meeting> meetings = agendaService_.listAllParticipateMeetings(userName_);
  printMeetings(meetings);
}

void AgendaUI::queryMeetingByTitle(void) {
  cout << "[query meetings] [title]:" << endl;
  cout << "[query meetings] ";
  string title;
  cin >> title;
  cout <<"[query meetings]" << endl;
  list<Meeting> ti = agendaService_.meetingQuery(userName_, title);
  printMeetings(ti);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
  cout << "[query meetings] ";
  string sDate, eDate;
  cin >> sDate >> eDate;
  cout << "[query meetings]" << endl;
  list<Meeting> meetings = agendaService_.meetingQuery(userName_, sDate, eDate);
  printMeetings(meetings);
}

void AgendaUI::deleteMeetingByTitle() {
  cout << "[delete meeting] [title]" << endl;
  cout << "[delete meeting] ";
  string title;
  cin >> title;
  if (agendaService_.deleteMeeting(userName_, title)) {
    cout << "[delete meeting by title] succeed!" << endl;
  } else {
    cout << "[error] delete meeting fail!" << endl;
  }
}

void AgendaUI::deleteAllMeetings() {
  if (agendaService_.deleteAllMeetings(userName_)) {
    cout << "[delete all meetings] succeed!" << endl;
  } else {
    cout << "[error] fail!" << endl;
  }
}

void AgendaUI::printMeetings(list<Meeting> meetings) {
  int lt = 5, ls = 7, lp = 11, lst = 10, let = 10;
  for (list<Meeting>::iterator iter = meetings.begin(); iter != meetings.end(); ++iter) {
    if (iter->getTitle().size() > lt) lt = iter->getTitle().size();
    if (iter->getSponsor().size() > ls) ls = iter->getSponsor().size();
    if (iter->getParticipator().size() > lp) lp = iter->getParticipator().size();
    if (Date::dateToString(iter->getStartDate()).size() > lst) lst = Date::dateToString(iter->getStartDate()).size();
    if (Date::dateToString(iter->getEndDate()).size() > let) let = Date::dateToString(iter->getEndDate()).size();
  }
  ++lt;++ls;++lp;++lst;++let;
  ++lt;++ls;++lp;++lst;++let;
  cout << left;
  cout << setw(lt) << "title  "  << setw(ls) << "sponsor  "  << setw(lp) << "paticipator  "
  << setw(lst) << "start time  " << std::setw(let) << "end time" << endl;
  for (list<Meeting>::iterator iter = meetings.begin(); iter != meetings.end(); ++iter) {
    cout << left << setw(lt) << iter->getTitle() << left << setw(ls) << iter->getSponsor() << left << setw(lp) << iter->getParticipator()
    << left << setw(lst) << Date::dateToString(iter->getStartDate()) << left << setw(let) << Date::dateToString(iter->getEndDate()) << endl;
  }
}
