#include <bits/stdc++.h>

using namespace std;

int getMax(const vector<int> &a, int n) {
  int ans = 0, cur = 0, pre = a[1];
  for (int i = 1; i <= n; i++) {
    if (a[i] == pre) {
      cur++;
    } else {
      cur = 1, pre = a[i];
    }
    ans = max(ans, cur);
  }
  return ans;
}

int modify(vector<int> &a, int dis, int n, int cnt) {
  for (int i = dis; i >= 1 && a[i] == a[dis + 1]; i--) {
    a[i] = cnt;
  }
  return getMax(a, n);
}

int main() {
  int n, m, maxCnt = 1;
  scanf("%d %d", &n, &m);
  
  vector<int> x(n + 10, 1), y(n + 10, 1), z(n + 10, 1);
  vector<bool> visx(n + 10, false), visy(n + 10, false), visz(n + 10, false);

  char op[5];

  int maxx = n, maxy = n, maxz = n;
  for (int i = 1, dis; i <= m; i++) {
    scanf("%s %d", op, &dis);
    if (dis == 0 || dis == n) {
      printf("%lld\n", 1ll * maxx * maxy * maxz);
      continue;
    }
    if (op[0] == 'x') {
      if (!visx[dis]) {
        visx[dis] = true;
        maxx = modify(x, dis, n, ++maxCnt);
      }
    } else if (op[0] == 'y') {
      if (!visy[dis]) {
        visy[dis] = true;
        maxy = modify(y, dis, n, ++maxCnt);
      }
    } else {
      if (!visz[dis]) {
        visz[dis] = true;
        maxz = modify(z, dis, n, ++maxCnt);
      }
    }
    printf("%lld\n", 1ll * maxx * maxy * maxz);
  }
  return 0;
}