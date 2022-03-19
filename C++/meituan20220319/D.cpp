// 可以考虑 另 p = lcm(k1, k2), f[i][j]，表示前i个数中模p余j的最大值，g[i][j]表示取到该值的方案。
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353;

int f[N][110], g[N][110], a[N], n, k1, k2, p;

int main() {
  cin >> n >> k1 >> k2;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  p = k1 * k2 / __gcd(k1, k2);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < p; j++) {
      f[i][j] = -0x3f3f3f3f;
    }
  }
  f[0][0] = 0, g[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < p; j++) {
      f[i][j] = max(f[i][j], f[i - 1][j]);
      // f[i - 1][j] -> (j + a[i]) % p + p % p
      int cur = ((j + a[i]) % p + p) % p;
      if (f[i - 1][j] != -0x3f3f3f3f) {
        f[i][cur] = max(f[i][cur], f[i - 1][j] + a[i]);
      }
    }
    for (int j = 0; j < p; j++) {
      // g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
      int cur = ((j + a[i]) % p + p) % p;
      if (f[i - 1][j] != -0x3f3f3f3f && f[i][cur] == f[i - 1][j] + a[i]) {
        g[i][cur] = (g[i][cur] + g[i - 1][j]) % mod;
      }
      if (f[i - 1][j] == f[i][j]) {
        g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
      }
    }
  }
  int ans = -0x3f3f3f3f, sum;
  for (int i = 0; i < p; i++) {
    if (i % k1 == 0 && i % k2 != 0) {
      if (f[n][i] > ans) {
        ans = f[n][i], sum = g[n][i];
      }
    }
  }
  cout << ans << " " << sum << endl;
  return 0;
}