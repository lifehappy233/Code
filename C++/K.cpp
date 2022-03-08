#include <bits/stdc++.h>

using namespace std;

const int N = 3e3 + 10, mod = 1000000007;

int f[N][N], n, m;

int main() {
  f[0][0] = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < N; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= 1) {
        f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;
      }
      if (j >= 2) {
        f[i][j] = (f[i][j] + f[i - 1][j - 2]) % mod;
      }
    }
  }
  int T;
  cin >> T;
  assert(T >= 1 && T <= 10000);
  while (T--) {
    cin >> n >> m;
    assert(n >= 1 && n <= 3000 && m >= 1 && m <= 3000);
    cout << f[n][m] << "\n";
  }
  return 0;
}