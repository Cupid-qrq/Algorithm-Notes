// 2026.2.26
// tag:最大流 最小割 Dinic
// AC方法：转化为平面图最短路问题，求最短路长度即为最小割容量
/*
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
  int to;
  ll cap;
  int rev;
};
int n, m, s, t;

vector<vector<Edge>> G;
vector<int> level, cur;

void add_edge(int u, int v, ll cap) {
  G[u].push_back({v, cap, (int)G[v].size()});
  G[v].push_back({u, 0, (int)G[u].size() - 1});
}

bool bfs(int s, int t) {
  fill(level.begin(), level.end(), -1);
  queue<int> q;
  level[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto &e : G[u]) {
      if (e.cap > 0 && level[e.to] == -1) {
        level[e.to] = level[u] + 1;
        q.push(e.to);
      }
    }
  }
  return level[t] != -1;
}

ll dfs(int u, int t, ll flow) {
  if (u == t)
    return flow;
  for (int &i = cur[u]; i < (int)G[u].size(); i++) {
    Edge &e = G[u][i];
    if (e.cap > 0 && level[e.to] == level[u] + 1) {
      ll pushed = dfs(e.to, t, min(flow, e.cap));
      if (pushed) {
        e.cap -= pushed;
        G[e.to][e.rev].cap += pushed;
        return pushed;
      }
    }
  }
  return 0;
}

ll dinic(int s, int t) {
  ll maxflow = 0;
  while (bfs(s, t)) {
    fill(cur.begin(), cur.end(), 0);
    while (ll f = dfs(s, t, LLONG_MAX))
      maxflow += f;
  }
  return maxflow;
}

inline int id(int x, int y) { return (x - 1) * m + y; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  int V = n * m + 5;
  G.assign(V, {});
  level.resize(V);
  cur.resize(V);
  s = id(1, 1);
  t = id(n, m);

  ll w;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      cin >> w;
      int u = id(i, j), v = id(i, j + 1);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> w;
      int u = id(i, j), v = id(i + 1, j);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      cin >> w;
      int u = id(i, j), v = id(i + 1, j + 1);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
  }

  cout << dinic(s, t) << "\n";

  return 0;
}
  */

// AC方法：平面图对偶图 + Dijkstra 最短路优化
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

struct Edge {
  int to;
  ll w;
};

int n, m, s, t;
vector<vector<Edge>> G;

ll dijkstra(int s, int t) {
  vector<ll> dist(t + 1, INF);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  dist[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue;

    for (auto [v, w] : G[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }
  return dist[t];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  // 特判：只有一行或一列
  if (n == 1 || m == 1) {
    ll ans = INF;
    if (n == 1) {
      for (int j = 1; j < m; j++) {
        ll w;
        cin >> w;
        ans = min(ans, w);
      }
    } else {
      for (int i = 1; i < n; i++) {
        ll w;
        cin >> w;
        ans = min(ans, w);
      }
    }
    cout << ans << "\n";
    return 0;
  }

  /* ==================== 平面图对偶图转换原理 ====================
   *
   * 【核心思想】
   * 原图：n×m 网格，源点(1,1)，汇点(n,m)
   * 对偶图：将原图的每个"面"作为节点
   *
   * 【面的定义】
   * - 外部面：网格外的无限区域
   * - 内部面：网格内被边围成的区域
   *
   * 对于 n×m 网格加斜边的情况：
   * - 每个格子(i,j到i+1,j+1)被斜边分成两个三角形面
   * - 共有 2*(n-1)*(m-1) 个三角形内部面
   *
   * 【关键转换】
   * 原图的边 -> 对偶图的边（连接该边两侧的面）
   * 原图的最小割 -> 对偶图的最短路
   */

  // 对偶图节点数：2*(n-1)*(m-1) 个三角形面 + 2 个外部面
  int V = 2 * (n - 1) * (m - 1) + 2;
  G.resize(V);

  s = 0;     // 源点：左上外部
  t = V - 1; // 汇点：右下外部

  // 每个格子内有两个三角形面：
  // 上三角形：由 (i,j), (i,j+1), (i+1,j+1) 围成
  // 下三角形：由 (i,j), (i+1,j), (i+1,j+1) 围成
  auto upper_id = [&](int i, int j) {
    return 2 * ((i - 1) * (m - 1) + (j - 1)) + 1;
  };
  auto lower_id = [&](int i, int j) {
    return 2 * ((i - 1) * (m - 1) + (j - 1)) + 2;
  };

  ll w;

  /* ==================== 横边建图 ====================
   *
   * 横边 (i,j)-(i,j+1)：
   *
   * i=1: 上方是源点s，下方是格子(1,j)的上三角形
   * i=n: 上方是格子(n-1,j)的下三角形，下方是汇点t
   * 1<i<n: 上方是格子(i-1,j)的下三角形，下方是格子(i,j)的上三角形
   */
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      cin >> w;
      if (i == 1) {
        G[s].push_back({upper_id(1, j), w});
        G[upper_id(1, j)].push_back({s, w});
      } else if (i == n) {
        G[lower_id(n - 1, j)].push_back({t, w});
        G[t].push_back({lower_id(n - 1, j), w});
      } else {
        G[lower_id(i - 1, j)].push_back({upper_id(i, j), w});
        G[upper_id(i, j)].push_back({lower_id(i - 1, j), w});
      }
    }
  }

  /* ==================== 竖边建图 ====================
   *
   * 竖边 (i,j)-(i+1,j)：
   *
   * j=1: 左方是汇点t，右方是格子(i,1)的下三角形
   * j=m: 左方是格子(i,m-1)的上三角形，右方是源点s
   * 1<j<m: 左方是格子(i,j-1)的上三角形，右方是格子(i,j)的下三角形
   */
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> w;
      if (j == 1) {
        G[lower_id(i, 1)].push_back({t, w});
        G[t].push_back({lower_id(i, 1), w});
      } else if (j == m) {
        G[s].push_back({upper_id(i, m - 1), w});
        G[upper_id(i, m - 1)].push_back({s, w});
      } else {
        G[upper_id(i, j - 1)].push_back({lower_id(i, j), w});
        G[lower_id(i, j)].push_back({upper_id(i, j - 1), w});
      }
    }
  }

  /* ==================== 斜边建图 ====================
   *
   * 斜边 (i,j)-(i+1,j+1)：
   * 分隔格子(i,j)内的上下两个三角形
   */
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      cin >> w;
      G[upper_id(i, j)].push_back({lower_id(i, j), w});
      G[lower_id(i, j)].push_back({upper_id(i, j), w});
    }
  }

  cout << dijkstra(s, t) << "\n";

  return 0;
}