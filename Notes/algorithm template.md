## *算法模板 C++*


### *1.1 快速读入*
```cpp
ios::sync_with_stdio(false);
cin.tie(0);
```
### *1.2 快速幂*
```cpp
long long qpow(long long a, long long b, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
```
### *1.3 欧几里得算法*
```cpp
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}
```




### *2.1 单调栈*
单调栈用于找到每个元素右边第一个比它大的元素的下标

算法的思路在于使用单调栈来维护一个递增的序列，遍历数组时，如果当前元素大于栈顶元素，则说明找到了栈顶元素的右边第一个比它大的元素，将栈顶元素出栈并记录结果，直到栈为空或当前元素不大于栈顶元素，然后将当前元素的下标入栈。
```cpp
stack<int> st;
for (int i = 0; i < n; i++)
{
    while (!st.empty() && num[i] > num[st.top()])
    {
        int idx = st.top();
        st.pop();
        res[idx] = i + 1; // 第n个数
    }
    st.push(i);
}
```

### *2.2 单调队列*
单调队列用于在滑动窗口中找到最大值或最小值，维护一个双端队列，队列中的元素保持单调递减（或递增），这样队首元素始终是当前窗口的最大值（或最小值）。在遍历数组时，先移除超出窗口范围的元素，然后移除队列中比当前元素小的元素，最后将当前元素入队。当窗口达到指定大小时，记录当前窗口的最大值。
```cpp
deque<int> dq;
for (int i = 0; i < n; i++)
{
    // 移除超出窗口的元素
    while (!dq.empty() && dq.front() <= i - k)
        dq.pop_front();
    // 维护单调递减：移除比当前小的元素
    while (!dq.empty() && arr[dq.back()] <= arr[i])
        dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) ans.push_back(arr[dq.front()]);
}
```

### *2.3 二分查找*
```cpp
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // 防止溢出
        if (arr[mid] == target) {
            return mid; // 找到目标值，返回索引
        } else if (arr[mid] < target) {
            left = mid + 1; // 目标值在右半部分
        } else {
            right = mid - 1; // 目标值在左半部分
        }
    }
    return -1; // 未找到目标值
}
```

### *2.4 二分答案*
```cpp
int left = 0, right = 1e9; // 根据问题调整范围
while (left < right) {
    int mid = left + (right - left) / 2;
    if (check(mid)) { // check 函数根据问题定义
        right = mid; // mid 是一个可行解，尝试更小的值
    } else {
        left = mid + 1; // mid 不是可行解，尝试更大的值
    }
}
return left; // 返回最小的可行解
```

### *2.5 定长滑动窗口*
比如解决定长数组中的最大值、最小值、平均值等问题
```cpp
int ans = 0, cnt = 0;
for (int i = 0; i < s.size(); i++) { // 枚举窗口右端点 i
    // 1. 右端点进入窗口
    if (/*右端点满足条件*/) {
        cnt++;
    }

    int left = i - k + 1; // 窗口左端点
    if (left < 0) { // 窗口大小不足 k，尚未形成第一个窗口
        continue;
    }
    // 2. 更新答案
    ans = max(ans, cnt);

    // 3. 左端点离开窗口，为下一个循环做准备
    char out = s[left];
    if (/*左端点满足条件*/) {
        cnt--;
    }
}
return ans;
```
### *2.6 KMP*
```cpp
// 构造KMP算法的next数组，next[i]表示s[0..i]的最长相等前后缀长度
vector<int> buildNext(const string &s)
{
    int m = s.length();
    vector<int> next(m, 0);
    int j = 0; // 前缀指针

    for (int i = 1; i < m; i++)
    {
        // 当前字符不匹配时，回退j到next[j-1]
        while (j > 0 && s[i] != s[j]) 
            j = next[j - 1];

        // 匹配则前缀长度加一
        if (s[i] == s[j])
            j++;

        next[i] = j; // 记录最长前后缀长度
    }
    return next;
}
// KMP主过程，查找substr在str中的所有出现位置
void KMP(const string &str, const string &substr)
{
    if (substr.empty())
        return;

    int n = str.length(), m = substr.length();
    vector<int> next = buildNext(substr); // 构造next数组

    int i = 0, j = 0; // i遍历主串，j遍历模式串
    for (; i < n; i++)
    {
        // 当前字符不匹配时，回退j到next[j-1]
        while (j > 0 && str[i] != substr[j])
        {
            j = next[j - 1];
        }
        // 匹配则j前进
        if (str[i] == substr[j])
            j++;

        // 匹配到完整模式串，输出位置（下标从1开始）
        if (j == m)
            cout << i - m + 2 << endl;
    }
    // 输出next数组，便于调试
    for (size_t i = 0; i < next.size(); i++)
        cout << next[i] << " ";
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    KMP(s1, s2); // 查找s2在s1中的所有位置
    return 0;
}
```


### *3.1 并查集*
初始化时每个节点的父节点指向自己，Find 函数用于查找某个节点的根节点，并在查找过程中进行路径压缩以优化后续查询。Union 函数用于合并两个节点所在的集合。
```cpp
int Find(int n)
{
    if (p[n] == n)
        return n;
    else
        return p[n] = Find(p[n]); // 路径压缩
}

void Union(int a, int b)
{
    int pa = Find(a);
    int pb = Find(b);
    if (pa != pb)
        p[pa] = pb; // 按秩合并
}

p.resize(n + 1);
for (int i = 1; i <= n; i++)
    p[i] = i;
```

### *3.2 Dijkstra*
```cpp
const int inf =INT_MAX;

vector<vector<pair<int, int>>> graph(n + 1); // 邻接表存储图，pair<节点, 权重>

for (int i = 0; i < m; i++) // m 条边 ,n 个节点
{
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w}); // 如果是无向图，还需要加上 graph[v].push_back({u, w});
}

vector<int> distance(n + 1, inf); // 初始化距离为无穷大
vector<bool> visited(n + 1, false); // 记录节点是否已访问

// 小根堆，实现优先队列，pair<距离, 节点>
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
distance[start] = 0; // 起点距离为0
pq.push({0, start});

while (!pq.empty())
{
    auto [dist, u] = pq.top();
    pq.pop();

    if (visited[u])
        continue;
    visited[u] = true;

    for (auto [v, w] : graph[u])
    {
        if (distance[u] + w < distance[v])
        {
            distance[v] = distance[u] + w;
            pq.push({distance[v], v});
        }
    }
}
```

### *3.3 floyd*
```cpp
const int inf = 1e9; // 定义一个足够大的值表示无穷大
vector<vector<int>> dist(n + 1, vector<int>(n + 1, inf));

for (int i = 1; i <= n; i++) // 初始化到自身距离为0
    dist[i][i] = 0;

for (int i = 1; i <= n; i++) // 输入边的信息
{
    for (int j = 1; j <= n; j++)
    {
        int w;
        cin >> w;
        dist[i][j] = min(dist[i][j], w);
    }
}

for (int k = 1; k <= n; k++) 
{
    for (int i = 1; i <= n; i++)
    {
        if (dist[i][k] == inf)
            continue;
        for (int j = 1; j <= n; j++)
        {
            if (dist[k][j] == inf)
                continue;
            if (dist[i][k] + dist[k][j] < dist[i][j])
            {
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
```

### *3.4 最小生成树Kruskal*
```cpp
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w; // 按权重升序排序
    }
};

vector<Edge> edges; // 存储所有边
vector<int> p; // 并查集父节点数组
// 并查集实现省略...

kruskal(int n){
    sort(edges.begin(), edges.end());
    int total = 0, cnt = 0;
    for (auto e : edges)
    {
        if (Union(e.u, e.v))
        {
            total += e.w;
            cnt++;
            if (cnt == n - 1)
            {
                break;
            }
        }
    }
}
```

### *3.5 网格 BFS*
适用于在二维网格中寻找最短路径或遍历所有可达节点。常见应用包括迷宫问题、岛屿数量统计等。
```cpp
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

struct Node {
    int x, y, step;
};

int n, m;
vector<vector<bool>> visited;
vector<vector<int>> grid; // 网格地图

int bfs(int sx, int sy, int ex, int ey) {
    queue<Node> q;
    visited.assign(n, vector<bool>(m, false));
    
    q.push({sx, sy, 0});
    visited[sx][sy] = true;

    while (!q.empty()) {
        auto [x, y, step] = q.front(); q.pop();
        
        if (x == ex && y == ey) return step; // 到达终点
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m 
                && !visited[nx][ny] && grid[nx][ny] != '#') { // 可通行
                visited[nx][ny] = true;
                q.push({nx, ny, step + 1});
            }
        }
    }
    return -1; // 无法到达
}
```

### *3.6 网格 DFS*
适用于在二维网格中寻找所有可达节点，常见应用包括岛屿数量统计、连通区域查找,或者国际象棋，扫雷等游戏中的路径搜索。
```cpp
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
vector<vector<bool>>& visited;

void dfs(int x, int y, vector<vector<char>>& grid) {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
        return;
    if (visited[x][y] || grid[x][y] == '0') // '0' 不可走
        return;

    visited[x][y] = true;

    // 向四个方向递归
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        dfs(nx, ny, grid, visited);
    }
}
```

### *4.1 一维前缀和与一维差分*
```cpp
// 一维前缀和
vector<int> pre(n + 1);
for (int i = 1; i <= n; i++)
    pre[i] = pre[i - 1] + arr[i - 1];

// 查询区间 [l, r] 和：pre[r] - pre[l-1]

// 一维差分（用于多次区间增减）
vector<int> diff(n + 2, 0);
// [l, r] 加 val：
diff[l] += val;
diff[r + 1] -= val;
// 最后做前缀和还原原数组
```

### *4.2 二维前缀和与二维差分*
```cpp
// 二维前缀和
vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + arr[i - 1][j - 1];
    }
}
// 查询子矩阵 (x1, y1) 到 (x2, y2) 的和：
// pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1];

// 二维差分（用于多次子矩阵增减）
vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));
// (x1, y1) 到 (x2, y2) 加 val：
diff[x1][y1] += val;
diff[x1][y2 + 1] -= val;
diff[x2 + 1][y1] -= val;
diff[x2 + 1][y2 + 1] += val;
// 最后做二维前缀和还原原数组
```

### *4.3 高精度加法*
```cpp
vector<int> A,B,C;
int add()
{
    string s1,s2;
    for(int i=s1.size()-1; i>=0; i--) A.push_back(s1[i]-'0'); 
    for(int i=s2.size()-1; i>=0; i--) B.push_back(s2[i]-'0');
    int t=0;
    for(int i=0; i<A.size() || i<B.size(); i++)
    {
        if(i<A.size()) t+=A[i];
        if(i<B.size()) t+=B[i];
        C.push_back(t % 10);
        t/=10;
    }
    if(t) C.push_back(1);
    for(int i=C.size()-1; i>=0; i--)
    cout<<C[i];
}
```

### *4.4 高精度乘法*
```cpp
vector<int> A,B,C;
int mul()
{
    string s1,s2;
    for(int i=s1.size()-1; i>=0; i--) A.push_back(s1[i]-'0'); 
    for(int i=s2.size()-1; i>=0; i--) B.push_back(s2[i]-'0');
    C.resize(A.size()+B.size(),0);
    for(int i=0; i<A.size(); i++)
        for(int j=0; j<B.size(); j++)
        {
            C[i+j]+=A[i]*B[j];
            C[i+j+1]+=C[i+j]/10;
            C[i+j]%=10;
        }
    while(C.size()>1 && C.back()==0) C.pop_back();
    for(int i=C.size()-1; i>=0; i--)
        cout<<C[i];
}
```
### *4.5 字符串哈希*
```cpp
// 字符串哈希模板，适用于快速判断子串是否相等
const int MOD = 1e9 + 7; // 取模用的大质数，防止溢出和哈希冲突
const int BASE = 131;    // 哈希基数，常用131或13331
vector<long long> hash, power; 
// hash[i]存储前i个字符的哈希值，power[i]存储BASE的i次幂

// 构建哈希和幂数组，便于后续O(1)获取任意子串哈希值
void buildHash(const string &s) {
    int n = s.length();
    hash.resize(n + 1, 0);   // hash[0] = 0，1-based
    power.resize(n + 1, 1);  // power[0] = 1
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * BASE + s[i - 1]) % MOD;
        // power[i] = BASE^i
        power[i] = (power[i - 1] * BASE) % MOD;
    }
}

// 获取子串 s[l..r] 的哈希值，l和r均为1-based下标
long long getHash(int l, int r) {
    // 利用前缀哈希和幂数组O(1)计算子串哈希值
    return (hash[r] - hash[l - 1] * power[r - l + 1] % MOD + MOD) % MOD;
}
```


### *5.1 01背包*
// 经典01背包问题，物品只能选或不选一次
```cpp
vector<int> dp(V + 1, 0); // V为背包容量
for (int i = 0; i < n; i++) { // n个物品
    for (int v = V; v >= w[i]; v--) { // 倒序遍历容量
        dp[v] = max(dp[v], dp[v - w[i]] + val[i]); // w[i]为物品体积，val[i]为价值
    }
}
```

### *5.2 完全背包*
// 每种物品可选无限次
```cpp
vector<int> dp(V + 1, 0);
for (int i = 0; i < n; i++) {
    for (int v = w[i]; v <= V; v++) { // 正序遍历容量
        dp[v] = max(dp[v], dp[v - w[i]] + val[i]);
    }
}
```

### *5.3 多重背包*
// 每种物品最多选s[i]次
```cpp
vector<int> dp(V + 1, 0);
for (int i = 0; i < n; i++) {
    for (int k = 1; k <= s[i]; k++) { // s[i]为物品数量
        for (int v = V; v >= w[i]; v--) {
            dp[v] = max(dp[v], dp[v - w[i]] + val[i]);
        }
    }
}
```

### *5.4 区间DP*
// 适用于区间合并、括号匹配等问题
```cpp
vector<vector<int>> dp(n, vector<int>(n, 0));
for (int len = 2; len <= n; len++) { // 枚举区间长度
    for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        dp[l][r] = ...; // 状态转移，具体问题具体分析
        for (int k = l; k < r; k++) {
            dp[l][r] = max(dp[l][r], dp[l][k] + dp[k+1][r]);
        }
    }
}
```

### *5.5 树形DP*
// 在树结构上进行动态规划，常用于求子树最优解
```cpp
vector<vector<int>> tree(n);
vector<int> dp(n, 0);
function<void(int, int)> dfs = [&](int u, int fa) {
    dp[u] = ...; // 初始化
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        dp[u] = ...; // 状态转移，具体问题具体分析
    }
};
dfs(root, -1);
```

### *5.6 状压DP*
// 用二进制压缩状态，适合集合类DP，如旅行商、选点覆盖等
```cpp
int N = ...; // 状态总数
vector<vector<int>> dp(N, vector<int>(n, INF));
dp[1 << start][start] = 0; // 例如TSP问题，起点start
for (int mask = 0; mask < (1 << n); mask++) {
    for (int u = 0; u < n; u++) {
        if (!(mask & (1 << u))) continue;
        for (int v = 0; v < n; v++) {
            if (mask & (1 << v)) continue;
            dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + cost[u][v]);
        }
    }
}
```

### *6. STL总结*
```cpp
// 1.排序
sort(v.begin(), v.end());                    // 升序
sort(v.begin(), v.end(), greater<int>());    // 降序
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;                            // 自定义比较
});

// 2.查找
find(v.begin(), v.end(), x);                 // 返回第一个等于 x 的迭代器
auto it = find(v.begin(), v.end(), x);
if (it != v.end()) index = it - v.begin();

// 3.二分查找
lower_bound(v.begin(), v.end(), x);          // 返回第一个不小于 x 的迭代器
upper_bound(v.begin(), v.end(), x);          // 返回第一个大于 x 的
binary_search(v.begin(), v.end(), x);        // 返回是否存在 x

// 4.最大值/最小值
int mx = *max_element(v.begin(), v.end());
int mn = *min_element(v.begin(), v.end());
auto [mn_it, mx_it] = minmax_element(v.begin(), v.end());

// 5.累加
accumulate(v.begin(), v.end(), 0);           // 初始值为 0
partial_sum(v.begin(), v.end(), v.begin()); // 前缀和

```