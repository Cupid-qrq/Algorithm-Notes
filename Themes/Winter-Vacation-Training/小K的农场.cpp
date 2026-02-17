#include <bits/stdc++.h>
using namespace std;

// 2025.12.3
// tag: 差分约束 

int n, m;
struct edge {
    int v, w;
};
const int inf = 1e9;
const int N = 5001;
vector<bool> inqueue;
vector<int> dis, cnt;
vector<edge> edges[N];

bool spfa(int s) {
    inqueue.assign(n + 1, false);
    dis.assign(n + 1, inf);
    cnt.assign(n + 1, 0);
    queue<int> q;
    q.push(s);
    inqueue[s] = true;
    cnt[s]++;
    dis[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for (auto& e : edges[u]) {
            if (dis[u] != inf && dis[u] + e.w < dis[e.v]) {
                dis[e.v] = dis[u] + e.w;
                if (!inqueue[e.v]) {
                    q.push(e.v);
                    inqueue[e.v] = true;
                    if (++cnt[e.v] > n) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int k, a, b, c;
        cin >> k;
        if (k == 1) {
            // a-b>=c -> b-a<= -c
            // from a to b ,weight -c
            cin >> a >> b >> c;
            edges[a].push_back({b, -c});
        } else if (k == 2) {
            // a-b<=c from b to a, weight c
            cin >> a >> b >> c;
            edges[b].push_back({a, c});
        } else {
            cin >> a >> b;
            edges[a].push_back({b, 0});
            edges[b].push_back({a, 0});
        }
    }

    int s = 0;
    for (int i = 1; i <= n; i++) {
        edges[s].push_back({i, 0});
    }

    if (spfa(s))
        cout << "Yes";
    else
        cout << "No";

    return 0;
}