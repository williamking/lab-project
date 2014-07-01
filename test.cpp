#include "Meeting.h"
#include "Date.h"
#include "Storage.h"
#include "User.h"
#include <iostream>
#include <string>
#include <functional>

using namespace std;

bool check(const User& user) {
  return (user.getName() == "Li");
}

int main() {
  Storage *st = Storage::getInstance();
  string file1 = "in.txt", file2 = "out.txt";
  User li;
  st->createUser(li);
  list<User> p = st->queryUser(check);
  for (list<User>::iterator iter = p.begin(); iter != p.end(); ++iter) {
    cout << iter->getName() << endl;
  }
  return 0;
}
