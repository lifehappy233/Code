#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int head[N], to[N], nex[N], value[N], cnt = 1;

int n, m, vis[N];

long long dis[N], f[N], g[N], h[N];

vector<pair<int, int>> G[N];

priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

vector<pair<long long, int>> vt;

void add(int x, int y, int w) {
  to[cnt] = y;
  nex[cnt] = head[x];
  value[cnt] = w;
  head[x] = cnt++;
  G[y].push_back({x, w});
}

void calc() {
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0;
  q.push({0, 1});
  while (q.size()) {
    int rt = q.top().second;
    q.pop();
    if (vis[rt]) {
      continue;
    }
    vis[rt] = 1;
    for (int i = head[rt]; i; i = nex[i]) {
      if (dis[to[i]] > dis[rt] + value[i]) {
        dis[to[i]] = dis[rt] + value[i];
        q.push({dis[to[i]], to[i]});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    vt.push_back({dis[i], i});
  }
  sort(vt.begin(), vt.end());
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1, u, v, w; i <= m; i++) {
    scanf("%d %d %d", &u, &v, &w);
    add(u, v, w);
  }
  calc();
  memset(g, 0x3f, sizeof(g));
  f[1] = g[1] = h[1] = 1;
  for (auto [d, u] : vt) {
    for (auto [v, w] : G[u]) {
      if (dis[u] == dis[v] + w) {
        f[u] += f[v];
        g[u] = min(g[u], g[v] + 1);
        h[u] = max(h[u], h[v] + 1);
      }
    }
  }
  printf("%lld %lld %lld %lld\n", dis[n], f[n], g[n] - 1, h[n] - 1);
  return 0;
}