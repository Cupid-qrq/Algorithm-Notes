// LCA模板题
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 7;
int n, m, s;
vector<int> tree[N];
int up[21][N], depth[N];

void dfs(int fa, int x) {
  up[0][x] = fa;
  depth[x] = depth[fa] + 1;
  for (int &nt : tree[x]) {
    if (nt == fa)
      continue;
    dfs(x, nt);
  }
}

int query(int a, int b) {
  if (depth[a] < depth[b])
    swap(a, b);

  for (int k = 20; k >= 0; k--)
    if (depth[a] - (1 << k) >= depth[b])
      a = up[k][a];

  if (a == b)
    return a;

  for (int k = 20; k >= 0; k--) {
    if (up[k][a] != up[k][b]) {
      a = up[k][a];
      b = up[k][b];
    }
  }
  return up[0][a];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> s;
  for (int i = 1; i <= n - 1; i++) {
    int x, y;
    cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  dfs(s, s);
  // 预处理倍增表
  for (int i = 1; i < 21; i++)
    for (int k = 1; k <= n; k++)
      up[i][k] = up[i - 1][up[i - 1][k]];

  int a, b;
  while (m--) {
    cin >> a >> b;
    cout << query(a, b) << '\n';
  }

  return 0;
}