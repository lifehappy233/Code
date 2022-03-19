#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5 + 10;

int a[N], b[N], c[N], d[N], n, m;

signed main() {
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
    cin >> d[i];
  }
  int sum = 0, cur = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i], cur += b[i];
    int p = 0;
    for (int j = 1; j <= m; j++) {
      if (sum >= c[j]) {
        p = j;
      }
    }
    int ans = sum - d[p];
    if (ans == cur) {
      putchar('B');
    } else if (ans < cur) {
      putchar('M');
    } else {
      putchar('Z');
    }
  }
  return 0;
}