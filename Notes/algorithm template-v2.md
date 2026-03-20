## 差分约束

```cpp
// 差分约束的核心思想是将每个变量视为图中的一个节点，
// 约束条件视为节点之间的有向边，边的权重表示变量之间的差值限制。
// 通过构建这样的图，我们可以使用最短路径算法（如 Bellman-Ford 或 SPFA）来检测是否存在负权环，
// 以及求解变量的最小值。
// 比如，约束条件 Xv - Xu <= w 可以转换为一条从 u 到 v 的有向边，权重为 w。
int n, m;
struct edge {
    int v, w;  // u->v w == Xv - Xu <= w
};
const int N = 5005;
vector<edge> edges[N];
vector<bool> inqueue;  // 是否在队列中
vector<int> cnt;       // 每个点入队次数
vector<int> dist;
const int inf = 1e9;

bool spfa(int s) {
    // 初始化
    dist.assign(n + 1, inf);
    cnt.assign(n + 1, 0);
    inqueue.assign(n + 1, false);
    queue<int> q;
    q.push(s);
    inqueue[s] = true;
    dist[s] = 0;
    cnt[s]++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for (auto& e : edges[u]) {
            // 松弛操作,遍历每条边,如果发现更短路径就更新
            if (dist[u] != inf && dist[u] + e.w < dist[e.v]) {
                dist[e.v] = dist[u] + e.w;
                // 该点不在队列中则加入队列
                if (!inqueue[e.v]) {
                    q.push(e.v);
                    inqueue[e.v] = true; 
                    // 如果某个点入队次数超过节点数，说明存在负权环
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
        int v, u, w;
        cin >> v >> u >> w;
        edges[u].push_back({v, w});
    }
    // 添加超级源点 s，连接到所有节点，权重为0
    // 这是为了确保所有节点都能被访问到
    int s = 0;
    for (int i = 1; i <= n; i++) {
        edges[s].push_back({i, 0});
    }
    if (spfa(s)) {
        for (int i = 1; i <= n; i++) {
            cout << dist[i] << " ";
        }
    } else {
        cout << "NO";
    }
    return 0;
}
```

## spfa

```cpp
int n, m;  // n个点 m条边
struct edge {
    int u, v, w;  // u->v w
};
vector<edge> edges;  // 边集
vector<int> dist;    // 距离
vector<bool> in_queue; // 是否在队列中
vector<int> cnt; // 记录每个点入队次数
const int inf = 1e9;

bool spfa(int s){
    dist.assign(n + 1, inf); // 初始化从起点到各点的距离为无穷大
    in_queue.assign(n + 1, false); // 初始化队列状态
    cnt.assign(n + 1, 0); // 初始化入队次数
    dist[s] = 0;    
    queue<int> q;
    q.push(s);
    in_queue[s] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for(auto& e : edges){
            if(e.u==u){
                if(dist[u] != inf && dist[u] + e.w < dist[e.v]){
                    dist[e.v] = dist[u] + e.w;
                    if(!in_queue[e.v]){
                        q.push(e.v);
                        in_queue[e.v] = true;
                        cnt[e.v]++;
                        if(cnt[e.v] > n) return false; // 存在负权环
                    }
                }
            }
        }
    }
    return true; // 不存在负权环
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int s = 1;  // 起点
    if (spfa(s)) {
        for (int i = 1; i <= n; i++) {
            cout << "dist[" << i << "] = " << dist[i] << "\n";
        }
    } else {
        cout << "exist negative cycle\n";
    }

    return 0;
}
```

## tarjan

```cpp
// Tarjan 算法模板，用于求解强连通分量
// 该算法使用深度优先搜索（DFS）来发现图中的强连通分量。
// 强连通分量是指在有向图中，任意两个节点都可以互相到达的最大子图。

const int N = 100005;
vector<int> g[N];  // 邻接表
int n, m;          // 节点数，边数
int dfn[N], low[N], idx; //用于记录节点的访问次序和能追溯到的最早节点
bool inStack[N];   // 标记节点是否在栈中
stack<int> st; 
int sscCnt,sccId[N]; // 强连通分量计数器及每个节点所属的强连通分量编号,ssc表示strongly connected component
vector<int> ssc[N]; // 每个强连通分量包含的节点列表

void tarjan(int u){
    dfn[u] = low[u] = ++idx; // 初始化dfn和low
    st.push(u);
    inStack[u] = true;

    for(int v : g[u]){
        if(!dfn[v]){ // 如果v未被访问
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]){ // 如果v在栈中，说明找到了一个回边
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 如果u是一个强连通分量的根节点
    if(dfn[u] == low[u]){
        sscCnt++;
        int x;
        do{
            x = st.top(); st.pop();
            inStack[x] = false;
            sccId[x] = sscCnt; // 标记节点所属的强连通分量编号
            ssc[sscCnt].push_back(x); // 将节点加入当前强连通分量
        } while(x != u);
    }
}

int main() {    
    cin >> n >> m;
    // 读入图
    for (int i = 0; i < m;i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
     
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            // 从未访问过的节点开始Tarjan
            tarjan(i);
        }
    }

    cout << sscCnt << "\n"; 
    for (int i = 1; i <= sscCnt; i++) {
        // 输出每个强连通分量的节点
        for (int node : ssc[i]) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}
```

## LCA
```cpp
// 倍增法LCA模板，支持O(logN)查询
const int N = 1e5 + 5, LOG = 20;
vector<int> tree[N]; // 邻接表存树
int fa[N][LOG];      // fa[u][k]: u的第2^k级祖先
int depth[N];        // depth[u]: u的深度

// 预处理，dfs建树并填充fa表
void dfs(int u, int f) {
    fa[u][0] = f; // u的父亲
    depth[u] = depth[f] + 1;
    for (int k = 1; k < LOG; ++k)
        fa[u][k] = fa[fa[u][k - 1]][k - 1]; // 倍增找祖先
    for (int v : tree[u]) {
        if (v != f) dfs(v, u);
    }
}

// 查询u和v的最近公共祖先
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v); // 保证u更深
    // 1. 先跳到同一深度
    for (int k = LOG - 1; k >= 0; --k)
        if (depth[fa[u][k]] >= depth[v])
            u = fa[u][k];
    if (u == v) return u;
    // 2. 同步向上跳，直到父亲相同
    for (int k = LOG - 1; k >= 0; --k)
        if (fa[u][k] != fa[v][k])
            u = fa[u][k], v = fa[v][k];
    return fa[u][0];
}

// 用法：
// 1. 建树 tree[u].push_back(v);
// 2. dfs(1, 0); // 假设1为根
// 3. lca(u, v); // 查询u和v的LCA
int main() {
    int n, m; // n个节点，m条边
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u); // 无向图
    }
    dfs(1, 0); // 从1号节点开始DFS，0号节点为虚拟根
    int q; // 查询次数
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n"; // 输出LCA
    }
    return 0;
}
``` 