#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int a[N], b[N], c[N], d[N], n, m;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
  }
  int sum = 0, cur = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i], cur += b[i];
    int ans = 0x3f3f3f3f, flag = 0;
    for (int j = 1; j <= m; j++) {
      if (sum >= c[j]) {
        flag = 1;
        ans = min(ans, sum - d[j]);
      }
    }
    if (flag) {
      if (ans > cur) {
        putchar('M');
      } else if (ans == cur) {
        putchar('B');
      } else {
        putchar('Z');
      }
    } else {
      if (sum == cur) {
        putchar('B');
      } else {
        putchar('Z');
      }
    }
  }
  return 0;
}