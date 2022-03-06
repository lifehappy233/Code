#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  int minMovesToMakePalindrome(string s) {
    int n = s.size(), ans = 0;
    if (n & 1) {
      for (int i = 0; i < n / 2; i++) {
        int p;
        for (int j = n - i - 1; ; j--) {
          if (s[j] == s[i]) {
            p = j;
            break;
          }
        }
        for (int j = p + 1; j <= n - i - 1; j++) {
          swap(s[j], s[j - 1]);
          ans++;
        }
      }
      return ans / 2;
    }
    
    return ans / 2;
  }
};

int main() {
  return 0;
}