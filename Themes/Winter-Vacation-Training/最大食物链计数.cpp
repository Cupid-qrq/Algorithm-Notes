#include <bits/stdc++.h>
using namespace std;

// 2025.12.17
// tag: 拓扑序DP O(V+E)

const int mod = 80112002;
const int N = 5001;
vector<int> g[N], indeg(N, 0), outdeg(N, 0);
int cnt[N];  // cnt[u]: 以 u 结尾的路径数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
            cnt[i] = 1;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            // 在toposort的过程中进行dp转移，累加路径数
            cnt[v] = (cnt[v] + cnt[u]) % mod;
            if (--indeg[v] == 0) q.push(v);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0) ans += cnt[i];
    }

    cout << ans % mod;
    return 0;
}