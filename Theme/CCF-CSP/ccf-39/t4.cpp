#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> edges[1001];
vector<int> weight(1001, 0);

int mex(vector<int>& v) {
    int n = v.size();
    vector<char> seen(n + 1, 0);

    for (int x : v)
        if (0 <= x && x <= n)  
            seen[x] = 1;

    for (int i = 0; i <= n; i++)
        if (!seen[i]) return i;

    return n + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> weight[i];

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        if (x == y) {
            cout << (weight[x] ? 0 : 1) << endl;
            continue;
        }
        vector<int> vis(n + 1, 0),parent(n+1,-1),path;
        parent[x] = x;
        vis[x] = 1;
        queue<int> q;
        q.push(x);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur == y) break;

            for (auto& next : edges[cur]) {
                if (!vis[next]) {
                    vis[next] = 1;
                    parent[next] = cur;
                    q.push(next);
                }
            }
        }
        int cur = y;
        while(cur!=-1){
            path.push_back(weight[cur]);
            if (cur == x) break;
            cur = parent[cur];
        }

        cout << mex(path) << endl;
    }
    return 0;
}
