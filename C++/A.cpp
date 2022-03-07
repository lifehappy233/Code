#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int sum[N], n, m;

bool judge() {
  for (int i = 1; i <= m; i++) {
    if (sum[i] == sum[i - 1]) {
      continue;
    }
    for (int j = i; j <= m; j += i) {
      int l = j, r = min(m, j + i - 1), k = j / i;
      if ((sum[r] - sum[l - 1]) && !(sum[k] - sum[k - 1])) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (int i = 1, x; i <= n; i++) {
      scanf("%d", &x);
      sum[x]++;
    }
    for (int i = 1; i <= m; i++) {
      sum[i] += sum[i - 1];
    }
    puts(judge() ? "Yes" : "No");
    for (int i = 1; i <= m; i++) {
      sum[i] = 0;
    }
  }
  return 0;
}