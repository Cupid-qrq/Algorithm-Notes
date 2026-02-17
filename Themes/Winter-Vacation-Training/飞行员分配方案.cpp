#include <bits/stdc++.h>
using namespace std;

// tag： 网络流应用--二分图匹配问题模板
// 用 Edmonds-Karp 实现, O(VE^2)
// 2025.12.23

struct edge {
    int to, cap, rev;
    edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {
    }
};
const int inf = 1e9;
vector<vector<edge>> graph;
vector<int> preV, preE;

void add(int u, int v) {
    graph[u].push_back({v, 1, (int)graph[v].size()});
    graph[v].push_back({u, 0, (int)graph[u].size() - 1});
}

int bfs(int s, int t) {
    fill(preV.begin(), preV.end(), -1);
    fill(preE.begin(), preE.end(), -1);
    queue<int> q;
    q.push(s);
    preV[s] = s;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t) break;
        int len = (int)graph[u].size();
        for (int i = 0; i < len; i++) {
            edge& e = graph[u][i];
            if (e.cap > 0 && preV[e.to] == -1) {
                preE[e.to] = i;
                preV[e.to] = u;
                q.push(e.to);
            }
        }
    }
    if (preE[t] == -1) return 0;

    int flow = inf;
    for (int v = t; v != s; v = preV[v]) {
        edge& e = graph[preV[v]][preE[v]];
        flow = min(flow, e.cap);
    }

    for (int v = t; v != s; v = preV[v]) {
        edge& e = graph[preV[v]][preE[v]];
        e.cap -= flow;
        graph[v][e.rev].cap += flow;
    }

    return flow;
}

int maxflow(int s, int t) {
    int f = 0;
    while (1) {
        int tmp = bfs(s, t);
        if (tmp == 0) break;
        f += tmp;
    }
    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    graph.resize(n + 2);
    preE.resize(n + 2);
    preV.resize(n + 2);

    int u, v;
    cin >> u >> v;
    while (u != -1 && v != -1) {
        add(u, v);
        cin >> u >> v;
    }

    int s = 0, t = n + 1;
    for (int i = 1; i <= m; i++) {
        add(s, i);
    }
    for (int i = m + 1; i <= n; i++) {
        add(i, t);
    }

    cout << maxflow(s, t) << '\n';
    for (int u = 1; u <= m; u++) {
        for (auto& e : graph[u]) {
            if (e.to >= m + 1 && e.to <= n && e.cap == 0) cout << u << " " << e.to << '\n';
        }
    }
    return 0;
}