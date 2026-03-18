// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// vector<vector<pair<int, ll>>> adj;

// struct DSU {
//   int n;
//   vector<int> p;

//   DSU(int n) : n(n), p(n + 1) {
//     for (int i = 1; i <= n; i++)
//       p[i] = i;
//   }

//   int find(int x) {
//     if (p[x] == x)
//       return x;
//     return p[x] = find(x);
//   }

//   void unite(int a, int b) {
//     int pa = find(a), pb = find(b);
//     if (pa != pb) {
//       p[pa] = pb;
//     }
//   }

//   bool check(int a, int b) { return find(a) == find(b); }
// };

// bool dfs(int fa, int cur, int to, ll dist, vector<char> &vis) {
//   if (cur == to) {
//     cout << dist << '\n';
//     return true;
//   }
//   vis[cur] = 1;
//   for (auto &[next, d] : adj[cur]) {
//     if (next != fa && !vis[next]) {
//       if (dfs(cur, next, to, dist + d, vis))
//         return true;
//     }
//   }
//   return false;
// }

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   int n, m, q;
//   cin >> n >> m >> q;
//   adj.assign(n + 1, {});
//   DSU dsu(n);

//   while (m--) {
//     int l, r;
//     ll s;
//     cin >> l >> r >> s;
//     adj[l].push_back({r, s});
//     adj[r].push_back({l, s});
//     dsu.unite(l, r);
//   }

//   while (q--) {
//     int u, v;
//     cin >> u >> v;
//     if (!dsu.check(u, v)) {
//       cout << "UNKNOWN" << '\n';
//     } else {
//       cout << "OK";
//       //   vector<char> vis(n + 1, 0);
//       //   dfs(-1, u, v, 0, vis);
//     }
//   }

//   return 0;
// }

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5 + 3;

struct edge {
  int to;
  ll w;
  edge(int v, ll w) : to(v), w(w) {}
};

vector<edge> g[N];
int n, m, q;
int color[N], p[N];
ll presum[N];
int cnt;

void dfs(ll sum, int cur, int cnt) {
  presum[cur] = sum;
  color[cur] = cnt;
  for (auto e : g[cur]) {
    if (!color[e.to])
      dfs(sum + e.w, e.to, cnt);
  }
}

int main() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    p[i] = i;

  while (m--) {
    int l, r;
    ll s;
    cin >> l >> r >> s;
    g[l - 1].push_back({r, s});
    g[r].push_back({l - 1, -s});
  }

  for (int i = 1; i <= n; i++) {
    if (!color[i])
      dfs(-1, i, ++cnt);
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    if (color[l - 1] != color[r])
      cout << "UNKNOWN" << '\n';
    else
      cout << presum[r] - presum[l - 1] << '\n';
  }
  return 0;
}
