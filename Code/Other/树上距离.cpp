// 带边权LCA

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 7, LOG = 20;
vector<pair<int, int>> tree[N];
int depth[N], dist[N], up[LOG + 1][N];
int n, q;

void dfs(int fa, int cur) {
  up[0][cur] = fa;
  depth[cur] = depth[fa] + 1;
  for (auto &e : tree[cur]) {
    if (e.first == fa)
      continue;
    dist[e.first] = dist[cur] + e.second;
    dfs(cur, e.first);
  }
}

int getlca(int u, int v) {
  if (depth[u] < depth[v])
    swap(u, v);
  for (int k = LOG; k >= 0; k--) {
    if (depth[u] - (1 << k) >= depth[v])
      u = up[k][u];
  }
  if (u == v)
    return u;
  for (int k = LOG; k >= 0; k--) {
    if (up[k][u] != up[k][v]) {
      u = up[k][u];
      v = up[k][v];
    }
  }
  return up[0][u];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  int u, v, l;
  for (int i = 1; i <= n - 1; i++) {
    cin >> u >> v >> l;
    tree[u].push_back({v, l});
    tree[v].push_back({u, l});
  }

  dfs(1, 1);
  for (int k = 1; k < LOG; k++)
    for (int u = 1; u <= n; u++)
      up[k][u] = up[k - 1][up[k - 1][u]];

  while (q--) {
    cin >> u >> v;
    cout << dist[u] + dist[v] - 2 * dist[getlca(u, v)] << '\n';
  }
  return 0;
}