#include <bits/stdc++.h>
using namespace std;

// 2025.12.17
// tag: 强连通分量，tarjan 
// tarjan的时间复杂度O(V+E)

const int N = 100005;
int n, m; // 节点数，边数
vector<int> g[N]; // 原图邻接表
int dfn[N], low[N], idx;  // dfn表示节点的dfs序，low表示节点能追溯到的最早节点
vector<bool> instack(N);
stack<int> st;
int sccId[N], sccCnt;  // sccId表示节点所属的强连通分量编号，sccCnt表示强连通分量数量
vector<int> scc[N];    // scc[i]表示第i个强连通分量包含的节点

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    st.push(u);
    instack[u] = true;

    for (int v : g[u]) {
        if (!dfn[v]) {
            // 如果v未被访问过，递归访问v，然后更新u的low值为u和v的low值的最小值
            // 保证low[u]能追溯到最早节点
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            // 如果v在栈中，说明找到了一个回边，更新u的low值为u的low值和v的dfn值的最小值
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 如果u的最早能追溯节点是自己，说明找到了一个强连通分量的根节点
    // 通过不断弹栈，直到弹出u为止，将这些节点都归为同一个强连通分量
    if (dfn[u] == low[u]) {
        int x;
        sccCnt++;
        do {
            x = st.top();
            st.pop();
            instack[x] = false;
            sccId[x] = sccCnt;
            scc[sccCnt].push_back(x);
        } while (x != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, a;
        cin >> u >> v >> a;
        g[u].push_back(v);
        if (a == 2) g[v].push_back(u);
    }

    // tarjan 求强连通分量
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    // 找出最大的强连通分量，同时字典序最小
    for (int i = 1; i <= sccCnt; i++) sort(scc[i].begin(), scc[i].end());
    vector<int> ans;
    int maxlen = -1;
    for (int i = 1; i <= sccCnt; i++) {
        int len = scc[i].size();
        if (len > maxlen) {
            maxlen = len;
            ans = scc[i];
        } else if (len == maxlen && scc[i] < ans) {  // vector可以直接比较字典序
            ans = scc[i];
        }
    }

    cout << maxlen << endl;
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}

/*
最后总结一下本道题目的算法设计和复杂度分析：
1. 算法设计
我们使用 Tarjan 算法来寻找有向图中的强连通分量（SCC）。Tarjan 算法通过深度优先搜索（DFS）遍历图，同时维护每个节点的访问时间戳（dfn）和能够追溯到的最早节点的时间戳（low）。当我们发现一个节点的 dfn 和 low 相等时，说明找到了一个强连通分量的根节点，我们可以通过弹栈将该强连通分量中的所有节点归为一类。最后，我们统计每个强连通分量的大小，并找出最大的强连通分量，同时在大小相同的情况下选择字典序最小的那个。

性能分析：
2. 时间复杂度
整个流程的时间复杂度主要有以下几个部分：
- 建图：O(m)，其中 m 是边的数量。
- Tarjan 算法：O(n + m)，其中 n 是节点数量，m 是边的数量。每个节点和边最多被访问两次。
- 统计强连通分量大小和找出最大强连通分量：O(n)，因为我们需要遍历所有节点来统计每个强连通分量的大小。
综上所述，整体时间复杂度为 O(n + m)。


3. 空间复杂度
空间复杂度主要由以下几个部分组成：
- 图的邻接表表示：O(n + m)。
- 辅助数组 dfn、low、sccId 和栈：O(n)。
因此，整体空间复杂度为 O(n + m)。
*/