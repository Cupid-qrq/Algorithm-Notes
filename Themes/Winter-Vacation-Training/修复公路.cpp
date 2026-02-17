#include <bits/stdc++.h>
using namespace std;

// 2025.12.17
// tag: 并查集，kruskal最小生成树 

struct dsu {
    int n;
    vector<int> p;
    dsu(int n) : n(n), p(n + 1) {
        for (int i = 1; i <= n; i++) {
            p[i] = i;
        }
    }

    int find(int x) {
        if (x == p[x]) return x;
        return x = find(p[x]);
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) p[rx] = ry;
    }
};

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {
    }
    bool operator<(const edge& other) {
        return w < other.w;  // w从小到大排序
    }
};

vector<edge> edges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    dsu d(n);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    int success_merge = 0, ans = 0;
    sort(edges.begin(), edges.end());
    for (auto& [u, v, w] : edges) {
        if (success_merge == n - 1) break;
        if (d.find(u) != d.find(v)) {
            d.unite(u, v);
            ans=max(ans,w);
            success_merge++;
        }
    }
    if (success_merge != n - 1)
        cout << -1;
    else
        cout << ans;
    return 0;
}