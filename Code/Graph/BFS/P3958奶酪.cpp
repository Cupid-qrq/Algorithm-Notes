// 2026.2.25
// tag: DSU or BFS

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// solution 1:BFS

struct Node {
  ll x, y, z;
  Node(ll x, ll y, ll z) : x(x), y(y), z(z) {}
  ll dist(Node other) {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) +
           (z - other.z) * (z - other.z);
  }
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

    // create graph
    vector<vector<int>> adj(n + 2);
    for (int i = 1; i <= n; i++) {
      if (ns[i].z - r <= 0) {
        adj[0].push_back(i);
        adj[i].push_back(0);
      }
    }

    for (int i = 1; i <= n; i++) {
      if (ns[i].z + r >= h) {
        adj[n + 1].push_back(i);
        adj[i].push_back(n + 1);
      }
    }

    ll base = 4 * r * r;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= i; j++) {
        if (i == j)
          continue;
        if (ns[i].dist(ns[j]) <= base) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }

    // BFS search
    vector<bool> vis(n + 2, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;
    bool found = false;
    while (!q.empty()) {
      int idx = q.front();
      q.pop();
      if (idx == n + 1) {
        found = true;
        break;
      }

      for (int t : adj[idx]) {
        if (!vis[t]) {
          vis[t] = true;
          q.push(t);
        }
      }
    }

    if (found) {
      cout << "Yes" << endl;
    } else
      cout << "No" << endl;
  }

  return 0;
}