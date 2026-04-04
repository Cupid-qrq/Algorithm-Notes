// 基环树+树形dp+环形dp

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> tree;
vector<int> fa, w;
vector<int> cycle;
int n;
vector<bool> vis, incylce;

// dp[u]：以 u 为端点，向其非环子树延伸能取得的最大链和（包含 u）。
vector<ll> dp;
ll ans_tree = 0;

bool get_cycle(int cur, int f) {
  // 在无向图 DFS 中，遇到已访问且不是父节点的点即可回溯出环。
  vis[cur] = true;
  fa[cur] = f;

  for (auto nt : tree[cur]) {
    if (nt == f)
      continue;
    if (!vis[nt]) {
      if (get_cycle(nt, cur))
        return true;
    } else {
      cycle.push_back(nt);
      for (int x = cur; x != nt; x = fa[x])
        cycle.push_back(x);
      return true;
    }
  }
  return false;
}

void dfs(int u, int father) {
  // 树上直径式转移：记录经过 u 的两条最大向下链。
  dp[u] = w[u];
  ll max1 = 0, max2 = 0;
  for (int v : tree[u]) {
    if (v == father || incylce[v])
      continue;
    dfs(v, u);
    if (dp[v] > max1) {
      max2 = max1;
      max1 = dp[v];
    } else if (dp[v] > max2) {
      max2 = dp[v];
    }
    dp[u] = max(dp[u], w[u] + dp[v]);
  }
  ans_tree = max(ans_tree, max1 + max2 + w[u]);
}

ll solve_cycle() {
  int k = cycle.size();
  if (k == 0)
    return LLONG_MIN;

  // 将环复制一倍，转为线性窗口问题，便于用单调队列做 O(k) 转移。
  vector<ll> a(2 * k + 1), b(2 * k + 1), pre(2 * k + 1, 0);
  for (int i = 1; i <= 2 * k; i++) {
    int id = cycle[(i - 1) % k];
    a[i] = w[id];
    b[i] = dp[id];
    pre[i] = pre[i - 1] + a[i];
  }

  // score(i,j)=b[i]+b[j]+sum(a[i+1..j-1])，并限制 1<=j-i<=k-1，
  // 即在复制后的数组里维护长度不超过 k-1 的合法配对。
  ll ans_cycle = LLONG_MIN;
  deque<int> q;
  for (int j = 1; j <= 2 * k; j++) {
    // 弹掉不在合法窗口内的左端点。
    while (!q.empty() && q.front() < j - k + 1) {
      q.pop_front();
    }

    if (!q.empty()) {
      int i = q.front();
      ans_cycle = max(ans_cycle, (b[i] - pre[i]) + (b[j] + pre[j - 1]));
    }

    // 维护 b[i]-pre[i] 的单调递减队列，队首始终为当前最优 i。
    ll cur = b[j] - pre[j];
    while (!q.empty() && (b[q.back()] - pre[q.back()]) <= cur) {
      q.pop_back();
    }
    q.push_back(j);
  }

  return ans_cycle;
}

int main() {
  cin >> n;

  // 按输入规模初始化，避免无效的大规模预分配。
  tree.assign(n + 1, {});
  fa.assign(n + 1, 0);
  w.assign(n + 1, 0);
  vis.assign(n + 1, false);
  incylce.assign(n + 1, false);
  dp.assign(n + 1, 0);

  for (int i = 1; i <= n; i++)
    cin >> w[i];
  for (int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  // 1) 找出唯一环。
  get_cycle(1, -1);
  for (int x : cycle)
    incylce[x] = true;

  // 2) 以每个环点为根，计算挂树贡献与树内最优答案。
  for (int node : cycle) {
    dfs(node, -1);
  }

  // 3) 在环上合并各环点贡献。
  ll ans_cycle = solve_cycle();

  // 最终答案：树内最优 与 环上合并最优 二者取大。
  cout << max(ans_tree, ans_cycle);
  return 0;
}