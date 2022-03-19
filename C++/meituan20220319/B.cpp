#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

char str[N], ans[N];

int n, m;

void solve1() {
  int p = 0, l, r;
  if (n & 1) {
    ans[++p] = str[n / 2 + 1];
    l = n / 2, r = n / 2 + 2;
  } else {
    l = n / 2, r = n / 2 + 1;
  }
  while (l) {
    ans[++p] = str[l--];
    ans[++p] = str[r++];
  }
}

void solve2() {
  int p = 1, l, r;
  if (n & 1) {
    ans[n / 2 + 1] = str[p++];
    l = n / 2, r = n / 2 + 2;
  } else {
    l = n / 2, r = n / 2 + 1;
  }
  while (l) {
    ans[l--] = str[p++];
    ans[r++] = str[p++];
  }
}

int main() {
  cin >> n >> m >> str + 1;
  if (m == 1) {
    solve1();
  } else {
    solve2();
  }
  cout << ans + 1 << endl;
  return 0;
}