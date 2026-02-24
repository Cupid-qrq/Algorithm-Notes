// 2026.2.25
// tag: DSU or BFS

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// solution 2：DSU

struct Node {
  ll x, y, z;
  Node(ll x, ll y, ll z) : x(x), y(y), z(z) {}
  ll dist(Node other) {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
           (z - other.z) * (z - other.z);
  }
};

struct DSU {
  vector<int> fa, sz;
  DSU(int n) : fa(n), sz(n, 1) { iota(fa.begin(), fa.end(), 0); }

  int find(int x) {
    if (fa[x] == x)
      return x;
    return fa[x] = find(fa[x]);
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return;
    if (sz[x] < sz[y])
      swap(x, y);
    fa[y] = x;
    sz[x] += sz[y];
  }

  bool same(int x, int y) { return find(x) == find(y); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll T;
  cin >> T;
  ll n, h, r;
  while (T--) {
    cin >> n >> h >> r;

    vector<Node> ns(n + 1, Node(0, 0, 0));
    ll x, y, z;
    for (int i = 1; i <= n; i++) {
      cin >> x >> y >> z;
      ns[i] = Node(x, y, z);
    }

    // DSU 建图：0 表示底部虚点，n+1 表示顶部虚点
    DSU dsu(n + 2);

    // 与底部相交的球，与 0 合并
    for (int i = 1; i <= n; i++) {
      if (ns[i].z - r <= 0)
        dsu.unite(0, i);
    }

    // 与顶部相交的球，与 n+1 合并
    for (int i = 1; i <= n; i++) {
      if (ns[i].z + r >= h)
        dsu.unite(n + 1, i);
    }

    // 任意两球相交则连边
    ll base = 4 * r * r;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        if (ns[i].dist(ns[j]) <= base)
          dsu.unite(i, j);
      }
    }

    if (dsu.same(0, n + 1))
      cout << "Yes" << '\n';
    else
      cout << "No" << '\n';
  }

  return 0;
}