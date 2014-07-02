#include "AgendaService.h"

using std::string;
using std::list;

AgendaService::AgendaService() {
  storage_ = Storage::getInstance();
}

AgendaService::~AgendaService() {
  delete storage_;
}

bool AgendaService::userLogIn(string userName, string password) {
  list<User> result = storage_->queryUser([userName, password](const User &user) {
    if (user.getName() == userName) && (user.getPassword() == password)) return true;
    return false;
  });
  if (result.size() == 0) return false;
  return true;
}

bool AgendaService::userRegister(string userName, string password, string, email, string phone) {
  list<User> find = storage->queryUser([userName, email, password, phone](const User &user) {
    if (user.getName() == userName) return true;
  });
  if (find.size() != 0) return false;
  User newUser(username, password, email, phone);
  storage_->createUser(newUser);
  return true;
}

bool AgendaService::deleteUser(string userName, string password) {
  int num = storage->deleteUser([userName, password](User &user) {
    if ((user.getName() == userName) && (user.getPassword() == password)) return true;
  }
  if (num != 0) return true;
  else return false;
}

list<User> AgendaService::listAllUsers(void) {
  return storage_->queryUser([](User&) { return true; });
}

bool AgendaService::createMeeting(string userName, string title, string participator, string startDate, string endDate) {
  Meeting newMeeting(userName, participator, startDate, endDate, title);
  if ((!newMeeting.getStartDate().isValid()) || (!newMeeting.getEndDate().isValid())) return false;
  if (newMeeting.getStartDate() >= newMeeting.getEndDate()) return false;
  //check if time is valid
  if (storage_->queryUser([userName](const User &user) {
    if (user.getName() == userName) return true;
    return false;
  }).size() == 0) return false;
  if (storage_->queryUser([participator](const User &user) {
    if (user.getName() == participator) return true;
    return false;
  }).size() == 0) return false;
  //check if the user and the participator exist
  if (storage_->queryMeeting([userName,title](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) && (meeting.getTitle() == title)) return true;
    else return false;
  }).size() != 0) return false;
  //check if the user's sponsored meeting title is unique
  list<Meeting> checker = storage_->queryMeeting([userName](Meeting &meeting) {
    if (meeting.getSponsor() == userName) return true;
    return false;
  });
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() > iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() < iter->getEndDate())) return false;
  }
  checker = storage_->queryMeeting([userName](const Meeting &meeting) {
    if (meeting.getParticipator() == userName) return true;
    return false;
  });
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() > iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() < iter->getEndDate())) return false;
  }
  checker = storage_->queryMeeting([userName](const Meeting &meeting) {
    if (meeting.getSponsor() == participator) return true;
    return false;
  });
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() > iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() < iter->getEndDate())) return false;
  }
  checker = storage_->queryMeeting([userName](const Meeting &meeting) {
    if (meeting.getParticipator() == participator) return true;
    return false;
  });
  for (list<Meeting>::iterator iter = checker.begin(); iter != checker.end(); ++iter) {
    if ((newMeeting.getStartDate() > iter->getStartDate()) && (newMeeting.getStartDate() < iter->getEndDate())) return false;
    if ((newMeeting.getEndDate() > iter->getStartDate()) && (newMeeting.getEndDate() < iter->getEndDate())) return false;
  }
  //check if the user and the participator have time
  storage_->createMeeting(newMeeting);
  return true;
}

list<Meeting> AgendaService::meetingQuery(string userName, string title) {
  return storage_.queryMeeting([userName, title](const Meeting &meeting) {
    if ((meeting.getSponsor() != userName) && (meeting->getParticipator() != userName)) return false;
    if (meeting((meeting.getTitle() != title) return false;
    return true;
  });
}

list<Meeting> AgendaService::meetingQuery(string userName, string startDate, string endDate) {
  Date sDate = Date::stringToDate(startDate), eDate = Date::stringToDate(endDate);
  return storage_->queryMeeting([userName, sDate, eDdate](const Meeting &meeting) {
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (meeting.getStartDate() >= sDate) && (meeting.getEndDate() <= eDate)) return true;
    else return false;
  });
}

list<Meeting> AgendaService::listAllMeetings(string userName) {
  return storage_->queryMeeting([userName](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName)) return true;
    else return false;
  });
}

list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
  return storage_->queryMeeting([userName](const Meeting &meeting) {
    if (meeting.getSponsor() == userName) return true;
    else return false;
  });
}

list<Meeting> AgendaService::listAllMeetings(string userName) {
  return storage_->queryMeeting([userName](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName)) return true;
    else return false;
  });
}

list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
  return storage_->queryMeeting([userName](const Meeting &meeting) {
    if (meeting.getParticipator() == userName) return true;
    else return false;
  });
}

bool AgendaService::deleteMeeting(string userName, string title) {
  return storage_->deleteMeeting([userName, title](const Meeting &meeting) {
    if (((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName))
    && (meeting.getTitle() == title)) return true;
  });
}

bool AgendaService::deleteAllMeetings(string userName) {
  return storage_->deleteMeeting([userName, title](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) || (meeting.getParticipator() == userName)) return true;
  });
}

void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
  storage_->sync();
}

