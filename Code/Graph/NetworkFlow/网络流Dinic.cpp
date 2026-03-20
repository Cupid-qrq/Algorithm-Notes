#include <bits/stdc++.h>
using namespace std;

// Dinic算法求解最大流模板

struct Edge {
    int to;
    long long cap;
    int rev;  // 反向边在邻接表中的位置
};

vector<vector<Edge>> G;
vector<int> level, cur;  // level[u]表示节点u的层次，cur[u]表示当前弧优化中u的当前边

void add_edge(int u, int v, long long cap) {
    G[u].push_back({v, cap, (int)G[v].size()});
    G[v].push_back({u, 0, (int)G[u].size() - 1});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1); // -1表示未访问
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& e : G[u]) {
            if (e.cap > 0 && level[e.to] == -1) { // 有剩余容量且未访问
                level[e.to] = level[u] + 1; // 设置层次
                q.push(e.to);
            }
        }
    }
    return level[t] != -1; // 是否能到达汇点
}

long long dfs(int u, int t, long long flow) {
    if (u == t) return flow; // 到达汇点，返回流量
    for (int& i = cur[u]; i < G[u].size(); i++) {
        Edge& e = G[u][i]; // 当前边
        if (e.cap > 0 && level[e.to] == level[u] + 1) {
            //  继续向下寻找增广路径,取min是为了限制流量不超过当前边的容量
            long long pushed = dfs(e.to, t, min(flow, e.cap));
            if (pushed) { // 如果找到了增广路径
                e.cap -= pushed;
                G[e.to][e.rev].cap += pushed;
                return pushed; // 返回当前的最大流量
            }
        }
    }
    return 0; // 没有找到增广路径
}

long long dinic(int s, int t) {
    long long maxflow = 0;
    // 不断构建分层网络并寻找增广路径
    while (bfs(s, t)) {
        // BFS构建分层网络后，重置当前弧优化数组
        fill(cur.begin(), cur.end(), 0);
        // 每一次分层后，不断DFS寻找增广路径，直到找不到为止
        while (long long f = dfs(s, t, LLONG_MAX)) {
            maxflow += f;
        }
    }
    return maxflow;
}

int main() {
    int n, m;
    cin >> n >> m;
    G.resize(n);
    level.resize(n);
    cur.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        add_edge(u, v, cap);
    }
    int s, t;
    cin >> s >> t;
    cout << dinic(s, t) << endl;
    return 0;
}