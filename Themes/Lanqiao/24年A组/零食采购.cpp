#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7, LOG = 20;
int n, q;
vector<int> c;
vector<int> g[N];
int up[LOG + 1][N], dep[N];
int pref[N][21]; // pref[u][x]：节点 u 到根路径上权值为 x 的节点数量

void dfs(int u, int fa) {
  up[0][u] = fa;
  dep[u] = dep[fa] + 1;

  for (int x = 1; x <= 20; x++) {
    pref[u][x] = pref[fa][x];
  }
  pref[u][c[u]]++;

  for (int v : g[u]) {
    if (v != fa) {
      dfs(v, u);
    }
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);
  }

  for (int k = LOG; k >= 0; k--) {
    if (dep[u] - (1 << k) >= dep[v])
      u = up[k][u];
  }

  if (u == v)
    return v;

  for (int k = LOG; k >= 0; k--) {
    if (up[k][u] != up[k][v]) {
      u = up[k][u];
      v = up[k][v];
    }
  }
  return up[0][u];
}

int query(int u, int v) {
  int k = lca(u, v), ans = 0;
  for (int x = 1; x <= 20; x++) {
    int cnt = pref[u][x] + pref[v][x] - 2 * pref[k][x] + (c[k] == x);
    if (cnt > 0)
      ans++;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> q;
  c.assign(n + 1, 0);

  for (int i = 1; i <= n; i++)
    cin >> c[i];

  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dep[0] = 0;
  dfs(1, 0);
  for (int i = 1; i <= LOG; i++) {
    for (int k = 1; k <= n; k++) {
      up[i][k] = up[i - 1][up[i - 1][k]];
    }
  }

  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << query(u, v) << '\n';
  }

  return 0;
}