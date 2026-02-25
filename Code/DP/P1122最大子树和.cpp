// 2026.2.25
// tag: dp 最大子数组和树版 kanade

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a, f;
vector<vector<int>> adj;

void dfs(int u, int parent) {
  f[u] = a[u]; // 初始化为自身权值

  for (int v : adj[u]) {
    if (v == parent)
      continue;

    dfs(v, u);

    if (f[v] > 0)
      f[u] += f[v];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  a.resize(n + 1);
  f.resize(n + 1);
  adj.resize(n + 1);

  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0);

  int ans = *max_element(f.begin() + 1, f.end());

  cout << ans;
  return 0;
}