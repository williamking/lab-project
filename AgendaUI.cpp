#include "AgendaService.h"
#include "AgendaUI.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stringstream>

using std::string;
using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::left;
using std::stringtream;

#define TARGET "17.17.0.25"

int out = 1;

AgendaUI::AgendaUI() {
  userName_ = "";
  userPassword_ = "";
  if ((host = gethostbyname(TARGET)) == NULL) {
    herror("gethostbyname fail!");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("create socket fail!");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket create fail!");
    exit(1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVERPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(my_addr.sin_zero), 8);
  if (bind(sockfd, (struct sockaddr *)& my_addr, sizeof(struct sockaddr)) == -1) {
  perror("bind error!");
  exit(1);
  }
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen error!");
    exit(1);
  }
}

void AgendaUI::OperationLoop(char *hostname) {
  do {
    if ((client_fd = accept(sockfd, (struct sockaddr*)&remote_addr, &sin_size)) == -1) {
      perror("accept error");
      continue;
    }
    if (userName_ == "") {
      send(client, "----------------------- Agenda-------------------------------\n", MAXDATASIZE, 0);
      send("Action :\n", MAXDATASIZE, 0);
      send("l   - log in Agenda by user name and pass word\n", MAXDATASIZE, 0);
      send("r   - register and Agenda account\n",MAXDATASIZE, 0);
      send("q   - quit Agenda\n", MAXDATASIZE, 0);
      send("-------------------------------------------------------------\n\n",
      MAXDATASIZE, 0);
      send("Agenda : ~$ ", MAXDATASIZE, 0);
      string op = getOperation();
      executeOperation(op);
    }
    if (userName_ != "") {
      send("----------------------- Agenda-------------------------------\n
Action :\n
o   - log out Agenda\n
dc  - delete Agenda account\n
lu  - list all Agenda user\n
cm  - create a meeeting\n
la  - list all meetings\n
las - list all sponsor meetings\n
lap - list all participate meetings\n
qm  - query meeting by title\n
qt  - query meeting by time interval\n
dm  - delete meeting by title\n
da  - delete all meetings\n
-------------------------------------------------------------\n",
      MAXDATASIZE, 0);
      string s = "Agenda@";
      s += userName_ + " : # ";
      send(s.to_str(), MAXDATASIZE, 0);
      "Action :" << endl;
      string op = getOperation();
      executeOperation(op);
    }
  } while (out);
}

void AgendaUI::startAgenda(void) {
}

string AgendaUI::getOperation() {
  string word;
  char buf[MAXDATASIZE];
  if ((recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
    perror("receive fail!");
    close(sockfd);
    exit(1);
  }
  buf[strlen(buf)] = '\0';
  word = buf;
  return word;
}

bool AgendaUI::executeOperation(string op) {
 bool k;
 if (userName_ == "") {
    if (op == string("l")) { userLogIn(); k = true; } else
    if (op == string("r")) { userRegister(); k = true; } else
    if (op == string("q")) { quitAgenda(); k = true; } else
    send("Invalid Command!\n",MAXDATASIZE, 0); k = false;
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
       send("Invalid Command!\n", MAXDATASIZE, 0); k = false;
     return k;
}

void AgendaUI::userLogIn(void) {
  string uName, pWord, str = "1";
  cout << "[log in] [user name] [password]" << endl;
  cout << "[log in] ";
  char buf[MAXDATASIZE];
  if ((recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
    perror("receive fail!");
    close(sockfd);
    exit(1);
  }
  buf[strlen(buf)] = '\0';
  string str = buf;
  uName = buf;
  pWord = buf;
  if (agendaService_.userLogIn(uName, pWord)) {
    send("[log in] succeed!\n", MAXDATASIZE, 0);
    userName_ = uName;
    userPassword_ = pWord;
  }
  else send(client_fd, "[error] log in fail!\n", MAXDATASIZE, 0);
}

void AgendaUI::userRegister(void) {
  string name, key, email, phone;
  send(client_fd, "[register] [user name] [password] [email] [phone]\n
[register] ", MAXDATASIZE, 0);
  if ((recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
    perror("receive fail!");
    close(sockfd);
    exit(1);
  }
  buf[strlen(buf)] = '\0';
  string str = buf;
  cin >> name >> key >> email >> phone;
  if (agendaService_.userRegister(name, key, email, phone)) {
    send("[register] succeed!\n", MAXDATASIZE, 0);
  } else {
    send(client_fd, "[error] register fail!\n", MAXDATASIZE, 0);
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
    send(client_fd, "[delete agenda account] succeed!\n", MAXDATASIZE, 0);
    userLogOut();
  } else {
    send(client_fd, "[delete agenda account] fail!\n", MAXDATASIZE, 0);
  }
}

void AgendaUI::listAllUsers(void) {
  send(client_fd, "[list all users]\n\n", MAXDATASIZE, 0);
  list<User> all = agendaService_.listAllUsers();
  int lName = 4, lEmail = 4, lPhone = 5;
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    if (iter->getName().size() > lName) lName = iter->getName().size();
    if (iter->getEmail().size() > lEmail) lEmail = iter->getEmail().size();
    if (iter->getPhone().size() > lPhone) lPhone = iter->getPhone().size();
  }
  stringstream ss;
  ss << left;
  ss << setw(lName) << "name" << "  " << setw(lEmail) << "email" << "  " << setw(lPhone) << "phone";
  string str;
  getline(ss, str);
  str += '\n';
  send(client_fd, str.to_str(), MAXDATASIZE, 0);
  for (list<User>::iterator iter = all.begin(); iter != all.end(); ++iter) {
    ss.clean();
    ss << left;
    ss << setw(lName) << iter->getName() << "  " << setw(lEmail) << iter->getEmail() << "  " << setw(lPhone) << iter->getPhone();
    getline(ss, str);
    str += '\n';
    send(client_fd, str.to_str(), MAXDATASIZE, 0);
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
