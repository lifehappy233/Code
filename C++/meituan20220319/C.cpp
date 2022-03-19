#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int l1[N], r1[N], l2[N], r2[N], a[N], b[N], len[N], sum1[N], sum2[N], T, n, m, cnt, tot;

int main() {
  cin >> T >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> l1[i];
    a[++cnt] = l1[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> r1[i];
    a[++cnt] = r1[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> l2[i];
    a[++cnt] = l2[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> r2[i];
    a[++cnt] = r2[i];
  }
  a[++cnt] = 1;
  a[++cnt] = T;
  sort(a + 1, a + 1 + cnt);
  cnt = unique(a + 1, a + 1 + cnt) - (a + 1);
  b[++tot] = a[1];
  len[tot] = 1;
  for (int i = 2; i <= cnt; i++) {
    if (a[i] != a[i - 1] + 1) {
      b[++tot] = a[i] - 1;
      len[tot] = a[i] - a[i - 1] - 1;
    }
    b[++tot] = a[i];
    len[tot] = 1;
  }
  for (int i = 1; i <= n; i++) {
    int p1 = lower_bound(b + 1, b + 1 + tot, l1[i]) - b;
    int p2 = lower_bound(b + 1, b + 1 + tot, r1[i]) - b;
    sum1[p1]++, sum1[p2 + 1]--;
  }
  for (int i = 1; i <= m; i++) {
    int p1 = lower_bound(b + 1, b + 1 + tot, l2[i]) - b;
    int p2 = lower_bound(b + 1, b + 1 + tot, r2[i]) - b;
    sum2[p1]++, sum2[p2 + 1]--;
  }
  int ans = 0;
  for (int i = 1; i <= tot; i++) {
    sum1[i] += sum1[i - 1];
    sum2[i] += sum2[i - 1];
    if (sum1[i] && sum2[i]) {
      ans += len[i];
    }
  }
  cout << ans << endl;
  return 0;
}