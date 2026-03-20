// 建反图+dfs

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> rg[N];
int n, m, A[N];

void dfs(int cur, int val) {
  if (A[cur] != -1)
    return; // Already assigned
  A[cur] = val;
  for (int &nt : rg[cur]) {
    dfs(nt, val);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    rg[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    A[i] = -1; // -1 means unassigned
  }
  // Process from n down to 1; first time a node is visited, assign it the largest reachable node
  for (int i = n; i >= 1; i--) {
    if (A[i] == -1) {
      dfs(i, i);
    }
  }

  for (int i = 1; i <= n; i++)
    cout << A[i] << " ";
  return 0;
}