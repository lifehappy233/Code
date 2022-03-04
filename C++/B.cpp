#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10, mod = 1e9 + 7;

int vis[N], f[N][3][3][3][10], n, m;

int main() {
  // freopen("out.txt", "w", stdout);
  scanf("%d %d", &n, &m);
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d %d", &x, &y);
    vis[x] |= 1 << (y - 1);
  }
  if (n < 3) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < 3; i++) {
    if (vis[1] >> i & 1) {
      continue;
    }
    for (int j = 0; j < 3; j++) {
      if (vis[2] >> j & 1) {
        continue;
      }
      for (int k = 0; k < 3; k++) {
        if (vis[3] >> k & 1) {
          continue;
        }
        if (i == 2 && j == 0 && k == 0) {
          puts("ok");
        }
        f[3][i][j][k][(1 << i) | (1 << j) | (1 << k)] = 1;
      }
    }
  }
  for (int i = 4; i <= n; i++) {
    for (int a = 0; a < 3; a++) {
      for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 3; c++) {
          for (int d = 0; d < 3; d++) {
            for (int statu = 0; statu < 8; statu++) { // int statu = 0; statu < 8; statu++
              if (vis[i] >> d & 1) {
                continue;
              }
              if ((statu >> d & 1) && a != d && b != d && c != d) {
                continue;
              }
              f[i][b][c][d][statu | (1 << d)] = (f[i][b][c][d][statu | (1 << d)] + f[i - 1][a][b][c][statu]) % mod;
            }
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        // cout << i + 1 << " " << j + 1 << " " << k + 1 << " " << f[n][i][j][k][7] << endl;
        ans = (ans + f[n][i][j][k][7]) % mod;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}