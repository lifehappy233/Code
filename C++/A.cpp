#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
  void get(int &a, int &b, string str) {
    int n = str.size(), cur = 0, f = 1;
    while (str[cur] != '+') {
      if (str[cur] == '-') {
        f = -1;
      }
      a = a * 10 + str[cur++] - '0';
    }
    a = a * f;
    cur++, f = 1;
    while (cur < n) {
      if (str[cur] == '-') {
        f = -1;
      }
      b = b * 10 + str[cur++] - '0';
    }
    b = b * f;
  }

public:
  string complexNumberMultiply(string num1, string num2) {
    int a = 0, b = 0, c = 0, d = 0;
    get(a, b, num1);
    get(c, d, num2);
  }
};

int main() {
  return 0;
}