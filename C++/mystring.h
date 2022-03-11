#ifndef __MYSTRING__
#define __MYSTRING__

#include <iostream>
#include <cstring>

class string {
private:
  char *mData;

public:
  string(const char *str);

  string(const string &str);

  string &operator = (const string &str);

  ~string();

  char *getStr() const {
    return mData;
  }
};

inline string::string(const char *str = 0) {
  if (str) {
    mData = new char[strlen(str) + 1];
    strcpy(mData, str);
  } else {
    mData = new char[1];
    *mData = '\0';
  }
}

inline string::string(const string &str) {
  mData = new char[strlen(str.mData) + 1];
  strcpy(mData, str.mData);
}

inline string &string::operator = (const string &str) {
  if (this == &str) {
    return *this;
  }
  delete[] mData;
  mData = new char[strlen(str.mData) + 1];
  strcpy(mData, str.mData);
  return *this;
}

std::ostream &operator << (std::ostream &os, const string &str) {
  return os << str.getStr();
}

inline string::~string() {
  delete[] mData;
}

#endif