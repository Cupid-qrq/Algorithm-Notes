// tag: 差分约束 (spfa最长路模型)

// 这题求的是一组解的和至少为多少,对应的是一组最大的解
// 则需要在松弛的时候反向操作,对应的判断为(dis[u]+w > dis[v])
// 求出每个点的最长路,此时的无解情况为存在正环
// 需要注意,最长路模型的建边为: u >= v + w  -> from u to v weight w

/* 旧代码
#include <bits/stdc++.h>
using namespace std;

int n, k;
const int inf = 1e9;
const int N = 100001;
struct edge {
    int v, w;
};
vector<int> dis, cnt;
vector<bool> inque;
vector<edge> edges[N];

// 
bool spfa(int s) {
    // spfa 求最长路模型
    dis.assign(n + 1, 0);        // 最长路初始化为0
    cnt.assign(n + 1, 0);        // 记录入队次数
    inque.assign(n + 1, false);  // 记录是否在队列中
    queue<int> q;
    q.push(s);
    inque[s] = true;
    cnt[s]++;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inque[cur] = false;
        for (auto& e : edges[cur]) { // 松弛操作
            if (dis[cur] + e.w > dis[e.v]) {  // 最长路模型反向松弛
                dis[e.v] = dis[cur] + e.w;
                if (!inque[e.v]) {
                    q.push(e.v);
                    inque[e.v] = true;
                    if (++cnt[e.v] > n) return false;// 检测是否存在正环
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> k;
    int x, a, b;
    while (k--) {
        cin >> x >> a >> b;
        switch (x) {
            case 1:
                // a=b double edge weight 0
                edges[a].push_back({b, 0});
                edges[b].push_back({a, 0});
                break;
            case 2:
                // a<b
                edges[a].push_back({b, 1});
                break;
            case 3:
                // a>=b
                edges[b].push_back({a, 0});
                break;
            case 4:
                // a>b
                edges[b].push_back({a, 1});
                break;
            case 5:
                // a<=b
                edges[a].push_back({b, 0});
                break;
            default:
                break;
        }
    }
    int s = 0;
    for (int i = 1; i <= n; i++) {
        edges[s].push_back({i, 1});
    }

    long long ans =0;
    if (spfa(s)) {
        for (int i = 1; i <= n; i++) {
            ans += dis[i];
        }
        cout << ans << endl;
    }else cout << -1 << endl;

    return 0;
}
*/

// 恶心的题目,在普通的spfa的基础上,少部分的用例TLE
// 需要进行优化,考虑改用tarjan+ 缩点+拓扑dp

// tag: 差分约束 (tarjan+缩点+拓扑dp)

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct Edge {
    int v, w;
};
vector<Edge> g[N];        // 原邻接图
// Tarjan 相关变量
vector<int> sccNodes[N];  // 每个 scc 的点集
int dfn[N], low[N], idx;  // dfn表示节点的访问次序，low表示能追溯到的最早节点
bool inStack[N];
stack<int> stk;
int sccId[N], sccCnt;  // sscCnt表示强连通分量的数量，sccId表示每个节点所属的强连通分量编号

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk.push(u);
    inStack[u] = true;

    for (auto [v, w] : g[u]) {
        if (!dfn[v]) {  // v未被访问
            tarjan(v);
            low[u] = min(low[u], low[v]);  // 维护low是否能追溯到更早的节点
        } else if (inStack[v]) {           // v在栈中，说明找到了一个回边
            low[u] = min(low[u], dfn[v]);  // 维护low是不是能追溯到更早的节点
        }
    }
    // 如果u的最早能追溯节点就是它自己, 则说明找到了一个强连通分量
    if (dfn[u] == low[u]) {
        sccCnt++;
        int x;
        do {
            x = stk.top();
            stk.pop();
            inStack[x] = false;
            sccId[x] = sccCnt;
            sccNodes[sccCnt].push_back(x);
        } while (x != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 建图
    auto addEdge = [&](int u, int v, int w) { g[u].push_back({v, w}); };
    // 超级源点 0 -> 所有点 >= 1
    for (int i = 1; i <= n; i++) {
        addEdge(0, i, 1);
    }
    // 处理约束
    for (int i = 0; i < k; i++) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) {  // a = b
            addEdge(a, b, 0);
            addEdge(b, a, 0);
        } else if (x == 2) {  // a < b  => b >= a+1
            addEdge(a, b, 1);
        } else if (x == 3) {  // a >= b => a >= b+0
            addEdge(b, a, 0);
        } else if (x == 4) {  // a > b => a >= b+1
            addEdge(b, a, 1);
        } else if (x == 5) {  // a <= b => b >= a+0
            addEdge(a, b, 0);
        }
    }

    // Tarjan
    for (int i = 0; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    // 如果某个强连通分量内存在正权边,则无解
    for (int u = 0; u <= n; u++) {
        for (auto [v, w] : g[u]) {
            if (sccId[u] == sccId[v] && w > 0) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    // 缩点后构建DAG图
    vector<vector<Edge>> dag(sccCnt + 1);
    vector<int> indeg(sccCnt + 1, 0);
    for (int u = 0; u <= n; u++) {
        for (auto [v, w] : g[u]) {
            int cu = sccId[u], cv = sccId[v];
            if (cu != cv) {
                dag[cu].push_back({cv, w});
                indeg[cv]++;
            }
        }
    }

    // 拓扑序DP
    vector<long long> dp(sccCnt + 1, 0);
    queue<int> q;
    dp[sccId[0]] = 0;// 超级源 SCC 的 dp 必须保证 =0

    for (int i = 1; i <= sccCnt; i++)
        if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : dag[u]) {
            dp[v] = max(dp[v], dp[u] + w);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    
    long long ans = 0;// 最终答案为每个点的 dp 之和
    for (int i = 1; i <= n; i++) {
        ans += dp[sccId[i]];
    }

    cout << ans << '\n';
    return 0;
}

/*
2.1 题目分析

如果 X=1 表示第 A 个小朋友分到的糖果必须和第 B 个小朋友分到的糖果一样多；
如果 X=2 表示第 A 个小朋友分到的糖果必须少于第 B 个小朋友分到的糖果；
如果 X=3 表示第 A 个小朋友分到的糖果必须不少于第 B 个小朋友分到的糖果；
如果 X=4 表示第 A 个小朋友分到的糖果必须多于第 B 个小朋友分到的糖果；
如果 X=5 表示第 A 个小朋友分到的糖果必须不多于第 B 个小朋友分到的糖果；

本体是一个经典的差分约束问题，要求在满足一系列不等式约束的前提下，计算变量的最小可能和。我们可以将每个变量视为图中的一个节点，而每个约束则对应于图中的一条有向边，边的权重表示变量之间的差值关系。而要求总糖果数最少，也就是求一组可行解的和至少为多少，相当于求每个节点的最大值之和。
需要注意的是，一般的差分约束的思路是通过对加权有向图进行松弛操作来求解最短路径，从而得到每个变量的最小值。并且在松弛过程中，如果发现存在负权环，则说明约束条件矛盾，无解。而在本题中，由于我们要求的是每个变量的最大值，因此需要采用的是最长路模型的差分约束，也就是在松弛操作中进行反向操作，即判断条件变为(dis[u]
+ w >
dis[v])。同样地，如果在松弛过程中发现存在正权环，则说明约束条件矛盾，无解。最终，我们可以通过对每个节点的最长路径值进行累加，得到满足所有约束条件下的变量最大值之和，即为所求的最小糖果数。
值得注意的是，在差分约束建图后，我们一般采用bellman-ford算法的优化版本spfa来进行松弛操作，但是在本本题中，由于题目的数据规模非常极端，spfa在部分测试点上会出现超时的情况。因此，我们需要采用tarjan算法来进行强连通分量的缩点处理，然后在缩点后的DAG图上进行拓扑排序和动态规划，从而高效地求解最长路径问题，避免了spfa在大规模数据下的性能瓶颈。这些在下面会给出具体实现说明。

2.2 算法实现
首先考虑建图部分，由于是最长路模型的差分约束，因此对于xi >= xj +
w的约束，我们需要从节点j向节点i添加一条权重为w的有向边。根据题目给出的五种约束类型，我们可以将它们分别转化为对应的边添加操作：
1. 对于X=1（xi = xj），需要添加两条边：一条从i到j，权重为0；另一条从j到i，权重为0。
2. 对于X=2（xi < xj），转化为xj >= xi + 1，因此添加一条从i到j，权重为1的边。
3. 对于X=3（xi >= xj），直接添加一条从j到i，权重为0的边。
4. 对于X=4（xi > xj），转化为xi >= xj + 1，因此添加一条从j到i，权重为1的边。
5. 对于X=5（xi <= xj），转化为xj >= xi + 0，因此添加一条从i到j，权重为0的边。
此外，为了确保每个变量至少为1，我们还需要添加一个超级源节点0，并从节点0向每个变量节点i添加一条权重为1的边，表示xi
>= 1。
然后是spfa的实现，我们维护一个队列用于存储待松弛的节点，同时维护每个节点的最长路径值dis[]，以及每个节点入队的次数cnt[]，用于检测正权环。在初始化时，将超级源节点0入队，并将其最长路径值设为0。然后不断从队列中取出节点u，遍历其所有出边(v,
w)，如果发现dis[u] + w >
dis[v]，则更新dis[v]的值，并将v入队。如果某个节点的入队次数超过n（节点总数），则说明存在正环，无解。
最后，我们只需将所有变量节点的最长路径值累加，即可得到满足所有约束条件下的变量最大值之和，即为所求的最小糖果数。
然而，题目的部分样例的数据规模时间庞大，在spfa实现的差分约束系统下出现了超时的情况。为了实现AC，我们只能对算法进行改进。分析原有的算法，spfa在处理大规模数据时，可能会因为频繁的入队和出队操作而导致效率低下。在图的边权较为复杂时，spfa的性能可能会退化到接近Bellman-Ford算法的水平，尤其是在存在大量边的情况下。这时候的时间复杂度可能会达到O(n*m)，其中n是节点数，m是边数，这在大规模数据下是不可接受的。

2.3 Tarjan + 缩点 + DAG 上动态规划

为了优化原有的 SPFA 实现，我们采用 Tarjan 算法进行强连通分量（SCC）分解，并在缩点后的 DAG 上进行动态规划求解。

1. **建图**：
   - 根据题目约束条件，将每个变量视为图中的一个节点，每个约束对应一条有向边，边权表示变量之间的差值关系。
   - 为了确保每个变量至少为 1，引入超级源点 0，并从 0 向每个节点添加一条权重为 1 的边。

2. **Tarjan 算法**：
   - 使用 Tarjan 算法对图进行 SCC 分解，找到所有强连通分量。
   - 在本题中，强连通分量任意两个节点之间可以互相到达，由前面差分约束建的图可以知道，如果这些点之间可以互相到达，则他们之间的糖果数必须相等，也就是都是建的权重为 0 的边。
   - 如果某个 SCC 内存在正权边，则说明约束条件矛盾，无解。

3. **缩点后的 DAG**：
   - 将每个 SCC 缩点为一个节点，构建新的 DAG。
   - 对于原图中的每条边，如果起点和终点分属不同的 SCC，则在 DAG 中添加一条边，权重保持不变。

4. **DAG 上动态规划**：
   - 在 DAG 上进行拓扑排序和动态规划，求解每个 SCC 的最大值。
   - 初始化超级源 SCC 的 DP 值为 0。
   - 对于每条边 u -> v，更新 dp[v] = max(dp[v], dp[u] + w)。
   - 最终答案为所有变量所属 SCC 的 DP 值之和。

5. **时间复杂度分析**：
   - **建图**：O(k)，其中 k 为约束条件的数量。
   - **Tarjan 算法**：O(n + m)，其中 n 为节点数，m 为边数。
   - **DAG 上动态规划**：O(n + m)。
   - **总复杂度**：O(n + m)。

通过上述优化，避免了 SPFA 在大规模数据下的性能瓶颈，能够高效解决题目要求。

时间复杂度上，首先建图的时间复杂度为 O(k)，其中 k 是约束条件的数量。Tarjan 算法的时间复杂度为 O(n + m)，其中 n 是节点数，m 是边数。最后在 DAG 上进行拓扑排序和动态规划的时间复杂度也是 O(n + m)。因此，总的时间复杂度为 O(n + m)，这在大规模数据下是可接受的，能够有效避免 SPFA 在某些情况下的性能瓶颈。

空间上，
*/