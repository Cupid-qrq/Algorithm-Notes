#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> c, d;
vector<vector<int>> t1, t2;
int ans = 0;

// 同时在两棵树上 DFS，u 是树1的当前节点，v 是树2的当前节点
void dfs(int u, int pu, int v, int pv, int depth) {
  if (c[u] != d[v])
    return;
  depth++;
  ans = max(ans, depth);

  for (int cu : t1[u]) {
    if (cu == pu)
      continue;
    for (int cv : t2[v]) {
      if (cv == pv)
        continue;
      if (c[cu] == d[cv]) {
        dfs(cu, u, cv, v, depth);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  t1.resize(n + 1);
  t2.resize(m + 1);
  c.resize(n + 1);
  d.resize(m + 1);

  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= m; i++)
    cin >> d[i];

  int u, v;
  for (int i = 1; i <= n - 1; i++) {
    cin >> u >> v;
    t1[u].push_back(v);
    t1[v].push_back(u);
  }
  for (int i = 1; i <= m - 1; i++) {
    cin >> u >> v;
    t2[u].push_back(v);
    t2[v].push_back(u);
  }

  dfs(1, -1, 1, -1, 0);

  cout << ans << endl;
  return 0;
}
