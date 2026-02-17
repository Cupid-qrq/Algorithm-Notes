#include <bits/stdc++.h>
using namespace std;

typedef pair<int, double> PID;
typedef pair<double, int> PDI;
const double inf = 1e18;

struct station {
  int x, y, r, t;
};

struct node {
  int x, y;
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<PID>> graph(n + m + 1);

  vector<node> nodes(n + m + 1);
  for (int i = 1; i <= n; i++) {
    cin >> nodes[i].x >> nodes[i].y;
  }

  for (int i = 1; i <= m; i++) {
    int x, y, r, t;
    cin >> x >> y >> r >> t;
    nodes[n + i] = {x, y};
    for (int k = 1; k <= n; k++) {
      int nx = nodes[k].x, ny = nodes[k].y;
      if (abs(nx - x) <= r && abs(ny - y) <= r) {
        double w = t / 2.0;
        graph[k].push_back({n + i, w});
        graph[n + i].push_back({k, w});
      }
    }
  }

  vector<double> dist(n + m + 1, inf);
  vector<bool> visited(n + m + 1, false);

  priority_queue<PDI, vector<PDI>, greater<>> pq;
  pq.push({0.0, 1});
  dist[1] = 0;

  while (!pq.empty()) {
    auto [distance, u] = pq.top();
    pq.pop();
    if (visited[u])
      continue;
    if (u == n)
      break;
    visited[u] = true;

    for (auto [v, w] : graph[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }

  if (dist[n] > 0) {
    cout << dist[n];
  } else {
    cout << "Nan";
  }

  return 0;
}
