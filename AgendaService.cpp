#include "AgendaService.h"
#include <functional>
#include <iostream>

using std::string;
using std::list;
using std::function;
using std::cout;
using std::endl;

AgendaService::AgendaService() {
  storage_ = Storage::getInstance();
}

AgendaService::~AgendaService() {
  delete storage_;
}

bool AgendaService::userLogIn(string userName, string password) {
  function<bool(const User&)> filter = [userName, password](const User &user) {
    if ((user.getName() == userName) && (user.getPassword() == password)) return true;
    return false;
  };
  list<User> result = storage_->queryUser(filter);
  if (result.size() == 0) return false;
  return true;
}

bool AgendaService::userRegister(string userName, string password, string email, string phone) {
  function<bool(const User&)> filter = [userName](const User &user) {
    if (user.getName() == userName) return true;
    else return false;
  };
  list<User> find = storage_->queryUser(filter);
  if (find.size() != 0) return false;
  User newUser(userName, password, email, phone);
  storage_->createUser(newUser);
  return true;
}

bool AgendaService::deleteUser(string userName, string password) {
  function<bool(const User&)> filter = [userName, password](const User &user) {
    if ((user.getName() == userName) && (user.getPassword() == password)) return true;
    else return false;
  };
  int num = storage_->deleteUser(filter);
  deleteAllMeetings(userName);
  if (num != 0) return true;
  else return false;
}

list<User> AgendaService::listAllUsers(void) {
  function<bool(const User&)> filter = [](const User&) { return true; };
  return storage_->queryUser(filter);
}

bool AgendaService::createMeeting(string userName, string title, string participator, string startDate, string endDate) {
  Date sDate = Date::stringToDate(startDate), eDate = Date::stringToDate(endDate);
  Meeting newMeeting(userName, participator, sDate, eDate, title);
  if ((Date::isValid(newMeeting.getStartDate()) == 0) || (Date::isValid(newMeeting.getEndDate()) == 0)) return false;
  if (newMeeting.getStartDate() >= newMeeting.getEndDate()) return false;
  //check if time is valid
  function<bool(const User&)> filter1 = [userName](const User &user) {
    if (user.getName() == userName) return true;
    return false;
  };
  function<bool(const User&)> filter2 = [participator](const User &user) {
    if (user.getName() == participator) return true;
    return false;
  };
  if (storage_->queryUser(filter1).size() == 0) return false;
  if (storage_->queryUser(filter2).size() == 0) return false;
  //check if the user and the participator exist
  function<bool(const Meeting&)> filter3 = [userName,title](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) && (meeting.getTitle() == title)) return true;
    else return false;
  };
  if (storage_->queryMeeting(filter3).size() != 0) return false;
  function<bool(const Meeting&)> filterx = [participator,title](const Meeting &meeting) {
    if ((meeting.getSponsor() == participator) && (meeting.getTitle() == title)) return true;
    else return false;
  };
  if (storage_->queryMeeting(filterx).size() != 0) return false;
  function<bool(const Meeting&)> filterx1 = [userName,title](const Meeting &meeting) {
    if ((meeting.getParticipator() == userName) && (meeting.getTitle() == title)) return true;
    else return false;
  };
  if (storage_->queryMeeting(filterx1).size() != 0) return false;
  function<bool(const Meeting&)> filterx2 = [participator,title](const Meeting &meeting) {
    if ((meeting.getParticipator() == participator) && (meeting.getTitle() == title)) return true;
    else return false;
  };
  if (storage_->queryMeeting(filterx2).size() != 0) return false;
  //check if the meeting title is unique
  function<bool(const Meeting&)> filter4 = [userName](const Meeting &meeting) {
    if (meeting.getSponsor() == userName) return true;
    else return false;
  };
  list<Meeting> checker = storage_->queryMeeting(filter4);
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() >= iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() <= iter->getEndDate())) return false;
    if ((newMeeting.getStartDate() < iter->getStartDate()) && (newMeeting.getEndDate() > iter->getEndDate())) return false;
  }
  function<bool(const Meeting&)> filter5 = [userName](const Meeting &meeting) {
    if (meeting.getParticipator() == userName) return true;
    return false;
  };
  checker = storage_->queryMeeting(filter5);
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() >= iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() <= iter->getEndDate())) return false;
    if ((newMeeting.getStartDate() < iter->getStartDate()) && (newMeeting.getEndDate() > iter->getEndDate())) return false;
  }
  function<bool(const Meeting&)> filter6 = [participator](const Meeting &meeting) {
    if (meeting.getSponsor() == participator) return true;
    return false;
  };
  checker = storage_->queryMeeting(filter6);
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() >= iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() <= iter->getEndDate())) return false;
    if ((newMeeting.getStartDate() < iter->getStartDate()) && (newMeeting.getEndDate() > iter->getEndDate())) return false;
  }
  function<bool(const Meeting&)> filter7 = [participator](const Meeting &meeting) {
    if (meeting.getParticipator() == participator) return true;
    return false;
  };
  checker = storage_->queryMeeting(filter7);
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() >= iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() <= iter->getEndDate())) return false;
    if ((newMeeting.getStartDate() < iter->getStartDate()) && (newMeeting.getEndDate() > iter->getEndDate())) return false;
  }
  //check if the user and the participator have time
  storage_->createMeeting(newMeeting);
  return true;
}

list<Meeting> AgendaService::meetingQuery(string userName, string title) {
  function<bool(const Meeting&)> filter = [userName, title](const Meeting &meeting) {
    if ((meeting.getSponsor() != userName) && (meeting.getParticipator() != userName)) return false;
    if (meeting.getTitle() != title) return false;
    return true;
  };
  return storage_->queryMeeting(filter);
}

list<Meeting> AgendaService::meetingQuery(string userName, string startDate, string endDate) {
  Date sDate = Date::stringToDate(startDate), eDate = Date::stringToDate(endDate);
  function<bool(const Meeting&)> filter = [userName, sDate, eDate](const Meeting &meeting) {
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (meeting.getStartDate() >= sDate) && (meeting.getEndDate() <= eDate)) return true;
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (sDate >= meeting.getStartDate()) && (sDate < meeting.getEndDate())) return true;
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (eDate > meeting.getStartDate()) && (eDate <= meeting.getEndDate())) return true;
    else return false;
  };
  return storage_->queryMeeting(filter);
}

list<Meeting> AgendaService::listAllMeetings(string userName) {
  function<bool(const Meeting&)> filter = [userName](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName)) return true;
    else return false;
  };
  return storage_->queryMeeting(filter);
}

list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
  function<bool(const Meeting&)> filter = [userName](const Meeting &meeting) {
    if (meeting.getSponsor() == userName) return true;
    else return false;
  };
  return storage_->queryMeeting(filter);
}

list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
  function<bool(const Meeting&)> filter = [userName](const Meeting &meeting) {
    if (meeting.getParticipator() == userName) return true;
    else return false;
  };
  return storage_->queryMeeting(filter);
}

bool AgendaService::deleteMeeting(string userName, string title) {
  function<bool(const Meeting&)> filter = [userName, title](const Meeting &meeting) {
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (meeting.getTitle() == title)) return true;
    else return false;
  };
  return storage_->deleteMeeting(filter);
}

bool AgendaService::deleteAllMeetings(string userName) {
  function<bool(const Meeting&)> filter = [userName](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName)) return true;
    return false;
  };
  return storage_->deleteMeeting(filter);
}

void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
  storage_->sync();
}

