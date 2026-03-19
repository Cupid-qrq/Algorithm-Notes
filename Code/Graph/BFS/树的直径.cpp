#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> tree[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  vector<int> dist(n + 1, -1);
  queue<int> q;
  q.push(1);
  dist[1] = 0;

  int idx = -1, maxd = -1;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (dist[cur] > maxd) {
      idx = cur;
      maxd = dist[cur];
    }

    for (int &nt : tree[cur]) {
      if (dist[nt] == -1) {
        dist[nt] = dist[cur] + 1;
        q.push(nt);
      }
    }
  }

  fill(dist.begin(), dist.end(), -1);
  q.push(idx);
  dist[idx] = 0;
  maxd = -1;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (dist[cur] > maxd) {
      idx = cur;
      maxd = dist[cur];
    }

    for (int &nt : tree[cur]) {
      if (dist[nt] == -1) {
        dist[nt] = dist[cur] + 1;
        q.push(nt);
      }
    }
  }

  cout << maxd;

  return 0;
}