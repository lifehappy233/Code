#include <bits/stdc++.h>

using namespace std;

const int N = 50;

long long p[N], k, ans;

int main() {
  p[0] = 1;
  for (int i = 1; i < N; i++) {
    p[i] = p[i - 1] * 3;
  }
  int n;
  cin >> n >> k;
  while (n--) {
    if (k <= p[n]) {
      ans++;
    } else if (k <= 2 * p[n]) {
      k -= p[n];
    } else {
      ans += 2;
      k -= 2 * p[n];
    }
  }
  cout << ans << endl;
  return 0;
}