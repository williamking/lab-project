#include "Date.h"
#include <string>
#include <sstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year = year_;
}

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getDay(void) const{
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

bool Date::isValid(Date date) {
  int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int monthDayForLeap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((date.year_ < 1000) || (date.year_ > 9999)) return false;
  if ((date.month_ < 1) || (date.month_ > 12)) return false;
  if (((date.year_ % 4 == 0) && (date.year_ % 100 != 0)) || (date.year_ % 400 == 0)) {
    if ((date.day_ < 1) || (date.day_ > monthDayForLeap[date.month_ - 1])) return false;
  }
  if ((date.year_ % 4 != 0) || ((date.year_ % 100 == 0) && (date.year_ % 400 != 0))) {
    if ((date.day_ < 1) || (date.day_ > monthDay[date.month_ - 1])) return false;
  }
  if ((date.hour_ < 0) || (date.hour_ > 23)) return false;
  if ((date.minute_ < 0) || (date.minute_ > 59)) return false;
  return true;
}

Date Date::stringToDate(std::string dateString) {
  string strYear, strHour, strMinute, strMonth, strDay;
  int year, hour, day, month, minute;
  strYear = dateString.substr(0, 4);
  strMonth = dateString.substr(5, 2);
  strDay = dateString.substr(8, 2);
  strHour = dateString.substr(11, 2);
  strMinute = dateString.substr(14, 2);
  stringstream reader;
  reader << strYear;
  reader >> year;
  reader.clear();
  reader << strMonth;
  reader >> month;
  reader.clear();
  reader << strDay;
  reader >> day;
  reader.clear();
  reader << strHour;
  reader >> hour;
  reader.clear();
  reader << strMinute;
  reader >> minute;
  return Date(year, month, day, hour, minute);
}
string Date::dateToString(Date date) {
  stringstream reader;
  reader << date.year_ << '-';
  if (date.month_ < 10) reader << '0';
  reader << date.month_ << '-';
  if (date.day_ < 10) reader << '0';
  reader << date.day_ << '/';
  if (date.hour_ < 10) reader << '0';
  reader << date.hour_ << ':';
  if (date.minute_ < 10) reader << '0';
  reader << date.minute_;
  string strDate;
  reader >> strDate;
  return strDate;
}
Date & Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;
  return *this;
}

bool Date::operator==(const Date& date) const {
  if (year_ != date.year_) return false;
  if (month_ != date.month_) return false;
  if (day_ != date.day_) return false;
  if (hour_ != date.hour_) return false;
  if (minute_ != date.minute_) return false;
  return true;
}

bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) return true;
  if (year_ < date.year_) return false;
  if (month_ > date.month_) return true;
  if (month_ < date.month_) return false;
  if (day_ > date.day_) return true;
  if (day_ < date.day_) return false;
  if (hour_ > date.hour_) return true;
  if (hour_ < date.hour_) return false;
  if (minute_ > date.minute_) return true;
  if (minute_ < date.minute_) return false;
  return false;
}

bool Date::operator<(const Date& date) const {
  if (year_ < date.year_) return true;
  if (year_ > date.year_) return false;
  if (month_ < date.month_) return true;
  if (month_ > date.month_) return false;
  if (day_ < date.day_) return true;
  if (day_ > date.day_) return false;
  if (hour_ < date.hour_) return true;
  if (hour_ > date.hour_) return false;
  if (minute_ < date.minute_) return true;
  if (minute_ > date.minute_) return false;
  return false;
}
  
bool Date::operator>=(const Date& date) const {
  return ((*this > date) || (*this == date));
}
 
bool Date::operator<=(const Date& date) const {
  return ((*this < date) || (*this == date));
}
