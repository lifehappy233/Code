#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int h[N], l[N], r[N], n;

long long sum[N], m;

bool calc(int x, int p, int l, int r) {
  long long need = 0;
  // [l + 1, p]
  if (l != p) {
    need += 1ll * (x + x - (p - l - 1)) * (p - l) / 2;
  }
  // [p, r - 1]
  if (r != p) {
    need += 1ll * (x + x - (r - 1 - p)) * (r - p) / 2;
  }
  need -= x;
  // cout << p << " " << l << " " << r << " " << need << endl;
  return need - (sum[r - 1] - sum[l]) <= m;
}

bool judge(int x) {
  for (int i = 1; i <= n; i++) {
    l[i] = r[i] = 0;
  }
  for (int i = 2, p = 2; i < n; i++) {
    while (p < i) {
      p++;
    }
    while (p <= n && h[p] < x - (p - i)) {
      p++;
    }
    if (p > n) {
      break;
    }
    r[i] = p;
  }
  for (int i = n - 1, p = n - 1; i >= 2; i--) {
    while (p > i) {
      p++;
    }
    while (p >= 1 && h[p] < x - (i - p)) {
      p--;
    }
    if (p < 1) {
      break;
    }
    l[i] = p;
  }
  for (int i = 1; i <= n; i++) {
    if (l[i] && r[i] && calc(x, i, l[i], r[i])) {
      return true;
    }
  }
  return false;
}

int main() {
  scanf("%d %lld", &n, &m);
  int l = 0, r = 2e9;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
    l = max(l, h[i]);
    sum[i] = sum[i - 1] + h[i];
  }
  // judge(5);
  while (l < r) {
    int mid = 1ll * l + r + 1 >> 1;
    // cout << l << " " << r << endl;
    if (judge(mid)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  printf("%d\n", l);
  return 0;
}