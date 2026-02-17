#include <bits/stdc++.h>
using namespace std;

// tag:  多状态dijkstra ，search 

const long long inf = 1e18;

struct edge {
    int v, w;
};

struct state {
    int u;
    int maxw;
    long long sum;
    bool operator<(const state& other) const {
        return sum > other.sum;
    }
};

vector<edge> edges[101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }

    vector<vector<long long>> dis(n + 1, vector<long long>(256, inf));
    priority_queue<state> pq;
    pq.push({1, 0, 0});
    dis[1][0] = 0;

    while (!pq.empty()) {
        auto [u, maxw, sum] = pq.top();
        pq.pop();
        if (sum > dis[u][maxw]) continue;
        for (auto& [v, w] : edges[u]) {
            int newMax = max(w, maxw);
            long long newSum = w + sum;
            if (newSum < dis[v][newMax]) {
                dis[v][newMax] = newSum;
                pq.push({v, newMax, newSum});
            }
        }
    }

    long long ans = inf;
    for (int mw = 0; mw <= 255; mw++) {
        if (dis[n][mw] != inf) ans = min(ans, dis[n][mw] + mw);
    }
    cout << ans;
    return 0;
}