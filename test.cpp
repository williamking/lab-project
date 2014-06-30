#include "Meeting.h"
#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  string sp = "william", par = "naruto", title = "fight!";
  Date st = Date::stringToDate("2006-05-14/18:00"), end = Date::stringToDate("2014-05-30/14:35");
  Meeting test(sp, par, st, end, title);
  cout << test.getParticipator() << endl;
  cout << test.getSponsor() << endl;
  cout << test.getStartDate().getDay() << endl;
  return 0;
}
