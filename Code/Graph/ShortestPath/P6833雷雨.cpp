// 2026.2.26
// tag: 最短路，图论

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e12;

struct Node {
  ll distance, x, y;
  bool operator<(const Node &other) const { return distance > other.distance; }
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m, a, b, c;
vector<vector<ll>> g(1001, vector<ll>(1001));
vector<vector<vector<ll>>> dist(3, vector<vector<ll>>(1001,
                                                      vector<ll>(1001, inf)));

bool check(int x, int y) { return x <= n && x >= 1 && y <= m && y >= 1; }

void dijkstra(int x, int y, int q) {
  priority_queue<Node> pq;
  pq.push({g[x][y], x, y});
  dist[q][x][y] = g[x][y];

  while (!pq.empty()) {
    auto [curd, cx, cy] = pq.top();
    pq.pop();

    if(curd!=dist[q][cx][cy])
      continue;

    for (int i = 0; i < 4; i++) {
      int nx = cx + dx[i], ny = cy + dy[i];
      if (check(nx, ny) && dist[q][nx][ny] > dist[q][cx][cy] + g[nx][ny]) {
        dist[q][nx][ny] = dist[q][cx][cy] + g[nx][ny];
        pq.push({dist[q][nx][ny], nx, ny});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> a >> b >> c;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      cin >> g[i][j];
  }

  dijkstra(1, a, 0);
  dijkstra(n, b, 1);
  dijkstra(n, c, 2);

  ll ans = dist[0][n][b] + dist[0][n][c];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans =
          min(dist[0][i][j] + dist[1][i][j] + dist[2][i][j] - 2 * g[i][j], ans);
    }
  }

  cout << ans;
  return 0;
}