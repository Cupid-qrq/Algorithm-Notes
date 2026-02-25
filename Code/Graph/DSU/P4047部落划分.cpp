// 2026.2.25
// tag: 生成树，并查集

#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int v1, v2;
  double dist;
  bool operator<(const Edge &other) const { return dist < other.dist; }
};

vector<int> p;
int Find(int a) {
  if (p[a] == a)
    return a;
  return p[a] = Find(p[a]);
}

bool Union(int a, int b) {
  int pa = Find(a);
  int pb = Find(b);
  if (pa == pb)
    return false;

  p[pa] = b;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<int> x(n + 1), y(n + 1);
  p.resize(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
    p[i] = i;
  }
  vector<Edge> edges;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      double dist =
          sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      edges.push_back({i, j, dist});
    }
  }

  // for (auto  &e : edges) {
  //   cout << e.v1 << " " << e.v2 << " " << e.dist << endl;
  // }

  // kruskal
  sort(edges.begin(), edges.end());
  int cnt = 0;
  for (auto &e : edges) {
    if (Union(e.v1, e.v2)) {
      cnt++;
      if (cnt == n - k+1) {
        cout << fixed << setprecision(2) << e.dist << endl;

        break;
      }
    }
  }

  return 0;
}