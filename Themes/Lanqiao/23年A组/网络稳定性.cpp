#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;
const int LOG = 20;
const int INF = 1e9;

int n, m, q;

struct Edge {
  int u, v, w;
};

vector<Edge> edges;
vector<pair<int, int>> g[N];
int up[LOG + 1][N], dep[N], me[LOG + 1][N];
int fa[N], vis[N], comp[N];

int find(int x) {
  if (fa[x] == x)
    return x;
  return fa[x] = find(fa[x]);
}

void kruskal() {
  sort(edges.begin(), edges.end(),
       [&](const Edge &a, const Edge &b) { return a.w > b.w; });

  int cnt = 0;
  for (auto &e : edges) {
    int ra = find(e.u), rb = find(e.v);
    if (ra == rb)
      continue;

    fa[ra] = rb;
    g[e.u].push_back({e.v, e.w});
    g[e.v].push_back({e.u, e.w});

    if (++cnt == n - 1)
      break;
  }
}

void dfs(int u, int f, int w, int c) {
  vis[u] = 1;
  comp[u] = c;
  up[0][u] = f;
  me[0][u] = w;
  dep[u] = (u == f ? 1 : dep[f] + 1);

  for (auto [v, ew] : g[u]) {
    if (v == f)
      continue;
    dfs(v, u, ew, c);
  }
}

int query(int x, int y) {
  if (comp[x] != comp[y])
    return -1;

  int ans = INF;
  if (dep[x] < dep[y])
    swap(x, y);

  for (int k = LOG; k >= 0; k--) {
    if (dep[up[k][x]] >= dep[y]) {
      ans = min(ans, me[k][x]);
      x = up[k][x];
    }
  }

  if (x == y)
    return ans;

  for (int k = LOG; k >= 0; --k) {
    if (up[k][x] != up[k][y]) {
      ans = min(ans, me[k][x]);
      ans = min(ans, me[k][y]);
      x = up[k][x];
      y = up[k][y];
    }
  }
  ans = min(ans, me[0][x]);
  ans = min(ans, me[0][y]);
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> q;
  edges.reserve(m);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  memset(me, 0x3f, sizeof(me));

  for (int i = 1; i <= n; ++i)
    fa[i] = i;

  kruskal();

  for (int i = 1; i <= n; i++) {
    if (!vis[i])
      dfs(i, i, INF, i);
  }

  for (int k = 1; k <= LOG; ++k) {
    for (int i = 1; i <= n; ++i) {
      up[k][i] = up[k - 1][up[k - 1][i]];
      me[k][i] = min(me[k - 1][i], me[k - 1][up[k - 1][i]]);
    }
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << query(x, y) << '\n';
  }

  return 0;
}
