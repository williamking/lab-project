#include "Storage.h"
#include "Meeting.h"
#include "User.h"
#include <fstream>
#include <functional>
#include <sstream>
#include <iostream>

using std::function;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::fstream;
using std::string;

Storage* Storage::instance_ = 0;

Storage::Storage() {
  readFromFile("agenda.data");
}

void Storage::createUser(const User& newUser) {
  userList_.push_back(newUser);
}

void Storage::createMeeting(const Meeting& newMeeting) {
  meetingList_.push_back(newMeeting);
}

bool Storage::readFromFile(const char *fpath) {
  fstream in(fpath);
  if (!in) return false;
  if (in.peek() == EOF) {
    in.close();
    return true;
  }
  string reader;
  getline(in, reader);
  unsigned int index = reader.size() - 2;
  int num = 0, ten = 1;
  while ((reader[index] >= '0') && (reader[index] <= '9')) { 
    num = num + (reader[index] - '0') * ten;
    ten *= 10;
    index--;
  }
  for (int i = 0; i < num; ++i) {
    getline(in, reader);
    int s = 0;
    string name = "";
    while (reader[s] != '\"') s++;
    s++;
    while (reader[s] != '\"') {
      name += reader[s];
      s++;
    }
    s++;
    string password = "";
    while (reader[s] != '\"') s++;
    s++;
    while (reader[s] != '\"') {
      password += reader[s];
      s++;
    }
    s++;
    string email = "";
    while (reader[s] != '\"') s++;
    s++;
    while (reader[s] != '\"') {
      email += reader[s];
      s++;
    }
    s++;
    string phone = "";
    while (reader[s] != '\"') s++;
    s++;
    while (reader[s] != '\"') {
      phone += reader[s++];
    }
    createUser(User(name, password, email, phone));
  }
  getline(in, reader);
  index = reader.size() - 2;
  num = 0, ten = 1;
  while ((reader[index] >= '0') && (reader[index] <= '9')) {
    num = num + (reader[index] - '0') * ten;
    ten *= 10;
    index--;
  }
  for (int i = 0; i < num; ++i) {
    int s = 0;
    getline(in, reader);
    while (reader[s] != '\"') s++;
    s++;
    string sponsor = "";
    while (reader[s] != '\"') {
      sponsor += reader[s++];
    }
    s++;
    while (reader[s] != '\"') s++;
    s++;
    string participator = "";
    while (reader[s] != '\"') {
      participator += reader[s++];
    }
    s++;
    while (reader[s] != '\"') s++;
    s++;
    string sdate = "";
    while (reader[s] != '\"') {
      sdate += reader[s++];
    }
    s++;
    Date sd = Date::stringToDate(sdate);
    while (reader[s] != '\"') s++;
    s++;
    string edate = "";
    while (reader[s] != '\"') {
      edate += reader[s++];
    }
    Date ed = Date::stringToDate(edate);
    s++;
    while (reader[s] != '\"') s++;
    s++;
    string title = "";
    while (reader[s] != '"') {
      title += reader[s++];
    }
    createMeeting(Meeting(sponsor, participator, sd, ed, title));
  }
  in.close();
  return true;
}

bool Storage::writeToFile(const char *fpath) {
  FILE *fp;
  if ((fp = fopen(fpath, "w")) == NULL) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  fstream out(fpath);
  if (!out) return false;
  int size = userList_.size();
  out << "{collection:\"User\", total:" << size << '}' << endl;
  list<User>::iterator iter = userList_.begin();
  for (; iter != userList_.end(); ++iter) {
    out << "{name:" << '\"' << iter->getName() << "\",password:\""
    << iter->getPassword() << "\",email:\"" << iter->getEmail()
    << "\",phone:\"" << iter->getPhone() << "\"}" << endl;
  }
  size = meetingList_.size();
  out << "{collection:\"Meeting\",total:" << size << '}' << endl;
  list<Meeting>::iterator iter2;
  for (iter2 = meetingList_.begin(); iter2 != meetingList_.end(); ++iter2) {
    out << "{sponsor:" << '\"' << iter2->getSponsor() << 
    "\",participator:\"" << iter2->getParticipator() << "\",sdate:\"" << Date::dateToString(iter2->getStartDate()) << "\",edate:\"" << Date::dateToString(iter2->getEndDate()) << "\",title:\""
<< iter2->getTitle() << "\"}" << endl;
  }
  out.close();
  return true;
}

Storage* Storage::getInstance(void) {
  if (instance_ == 0) instance_ = new Storage;
  return instance_;
}

Storage::~Storage() {
  sync();
  instance_ = 0;
}

list<User> Storage::queryUser(function<bool(const User&)> filter) {
  list<User> chosenUser;
  for (list<User>::iterator iter = userList_.begin(); iter != userList_.end(); iter++) {
    if (filter(*iter)) chosenUser.push_back(*iter);
  }
  return chosenUser;
}

int Storage::updateUser(function<bool(const User&)> filter, function<void(User&)> switcher) {
  list<User>::iterator iter = userList_.begin();
  int num = 0;
  for (; iter != userList_.end(); ++iter) {
    if (filter(*iter)) {
      switcher(*iter);
      ++num;
    }
  }
  return num;
}

int Storage::deleteUser(function<bool(const User&)> filter) {
  list<User>::iterator iter = userList_.begin();
  int num = 0;
  for (; iter != userList_.end();) {
    if (filter(*iter)) {
      iter = userList_.erase(iter);
      ++num;
    } else {
      ++iter;
    }
  }
  return num;
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting&)> filter) {
  list<Meeting> chosenMeeting;
 for (list<Meeting>::iterator iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
    if (filter(*iter)) chosenMeeting.push_back(*iter);
  }
  return chosenMeeting;
}

int Storage::updateMeeting(function<bool(const Meeting&)> filter, function<void(Meeting&)> switcher) {
  list<Meeting>::iterator iter = meetingList_.begin();
  int num = 0;
  for (; iter != meetingList_.end(); ++iter) {
    if (filter(*iter)) {
      switcher(*iter);
      ++num;
    }
  }
  return num;
}

int Storage::deleteMeeting(function<bool(const Meeting&)> filter) {
  list<Meeting>::iterator iter = meetingList_.begin();
  int num = 0;
  for (; iter != meetingList_.end(); iter++) {
    if (filter(*iter)) {
      ++num;
    }
  }
  meetingList_.remove_if(filter);
  return num;
}

bool Storage::sync(void) {
  return writeToFile("agenda.data");
}

