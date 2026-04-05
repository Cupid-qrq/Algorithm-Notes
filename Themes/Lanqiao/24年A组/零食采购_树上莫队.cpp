#include <bits/stdc++.h>
using namespace std;

/*
树上莫队（Mo on Tree）模板题：
给定一棵树，查询多组 (u, v)，求路径 u-v 上不同权值个数。

核心思想（先看这个再看代码）：
1) 普通莫队处理“数组区间”，树上路径不是数组区间。
2) 通过欧拉序把树“拉平”成长度 2n 的序列：每个点出现两次（入栈一次、出栈一次）。
3) 把路径查询 (u, v) 转换成欧拉序上的区间 [l, r]，再用莫队移动指针维护当前答案。
4) 维护规则不是“元素出现次数”，而是“点是否被选中（奇偶次）”：
   - 当前区间里某点出现奇数次 => 这个点在当前路径点集里
   - 偶数次 => 不在路径点集里
5) 对每次点加入/移除，更新该点颜色频次，并维护 distinct（颜色种类数）。

复杂度：
- 预处理：O(n log n)
- 莫队：约 O((n + q) * sqrt(n)) 次 toggle（常数与数据分布相关）
- 空间：O(n)
*/

struct Query {
  int l, r;  // 欧拉序区间
  int id;    // 原查询编号
  int extra; // 若 lca(u,v) 不在区间内，需要额外补这个点；否则为 0
  int block; // 分块号（排序用）
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> color(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }

  vector<vector<int>> g(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // ---------- 可选但推荐：颜色离散化 ----------
  // 即使本题颜色 <= 20，也保留这段，模板更通用。
  vector<int> allVals;
  allVals.reserve(n);
  for (int i = 1; i <= n; i++)
    allVals.push_back(color[i]);
  sort(allVals.begin(), allVals.end());
  allVals.erase(unique(allVals.begin(), allVals.end()), allVals.end());

  vector<int> compColor(n + 1);
  for (int i = 1; i <= n; i++) {
    compColor[i] = int(lower_bound(allVals.begin(), allVals.end(), color[i]) -
                       allVals.begin()) +
                   1;
  }
  int colorKind = (int)allVals.size();

  // ---------- LCA 预处理 + 欧拉序（迭代 DFS，避免深递归爆栈） ----------
  int LOG = 1;
  while ((1 << LOG) <= n)
    LOG++;

  vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
  vector<int> dep(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0);
  vector<int> euler(2 * n + 2, 0);

  struct Frame {
    int u, p, idx;
  };

  int timer = 0;
  vector<Frame> st;
  st.reserve(n);
  st.push_back({1, 0, 0});
  dep[1] = 0;
  up[0][1] = 0;

  while (!st.empty()) {
    Frame &cur = st.back();
    int u = cur.u, p = cur.p;

    if (cur.idx == 0) {
      // 第一次到达 u：记录入时刻
      tin[u] = ++timer;
      euler[timer] = u;
    }

    if (cur.idx < (int)g[u].size()) {
      int v = g[u][cur.idx++];
      if (v == p)
        continue;
      dep[v] = dep[u] + 1;
      up[0][v] = u;
      st.push_back({v, u, 0});
    } else {
      // 子节点都处理完：记录出时刻
      tout[u] = ++timer;
      euler[timer] = u;
      st.pop_back();
    }
  }

  for (int k = 1; k < LOG; k++) {
    for (int v = 1; v <= n; v++) {
      up[k][v] = up[k - 1][up[k - 1][v]];
    }
  }

  auto lca = [&](int u, int v) {
    if (dep[u] < dep[v])
      swap(u, v);
    int diff = dep[u] - dep[v];
    for (int k = 0; k < LOG; k++) {
      if (diff & (1 << k))
        u = up[k][u];
    }
    if (u == v)
      return u;
    for (int k = LOG - 1; k >= 0; k--) {
      if (up[k][u] != up[k][v]) {
        u = up[k][u];
        v = up[k][v];
      }
    }
    return up[0][u];
  };

  // ---------- 把路径查询转成欧拉序区间 ----------
  vector<Query> qs;
  qs.reserve(q);

  int blockSize = max(1, (int)sqrt(2 * n));

  for (int i = 0; i < q; i++) {
    int u, v;
    cin >> u >> v;
    if (tin[u] > tin[v])
      swap(u, v);

    int w = lca(u, v);
    Query qu;
    qu.id = i;

    if (w == u) {
      // 路径对应区间 [tin[u], tin[v]]，不需要额外点
      qu.l = tin[u];
      qu.r = tin[v];
      qu.extra = 0;
    } else {
      // 路径对应区间 [tout[u], tin[v]]，需额外补 lca
      qu.l = tout[u];
      qu.r = tin[v];
      qu.extra = w;
    }

    qu.block = qu.l / blockSize;
    qs.push_back(qu);
  }

  // 莫队排序：同块按 r 奇偶排序（蛇形）减少指针抖动
  sort(qs.begin(), qs.end(), [&](const Query &a, const Query &b) {
    if (a.block != b.block)
      return a.block < b.block;
    if (a.block & 1)
      return a.r > b.r;
    return a.r < b.r;
  });

  // ---------- 维护当前窗口答案 ----------
  vector<int> colorCnt(colorKind + 1, 0);
  vector<char> inPath(n + 1, 0); // 点是否在当前路径点集中（由奇偶控制）
  int distinct = 0;

  auto toggleNode = [&](int x) {
    int col = compColor[x];
    if (inPath[x]) {
      // 移出
      int &cnt = colorCnt[col];
      cnt--;
      if (cnt == 0)
        distinct--;
      inPath[x] = 0;
    } else {
      // 加入
      int &cnt = colorCnt[col];
      if (cnt == 0)
        distinct++;
      cnt++;
      inPath[x] = 1;
    }
  };

  auto togglePos = [&](int pos) { toggleNode(euler[pos]); };

  vector<int> ans(q, 0);
  int curL = 1, curR = 0;

  for (const auto &qu : qs) {
    while (curL > qu.l)
      togglePos(--curL);
    while (curR < qu.r)
      togglePos(++curR);
    while (curL < qu.l)
      togglePos(curL++);
    while (curR > qu.r)
      togglePos(curR--);

    if (qu.extra != 0) {
      // 该类查询需要补上 lca 节点，再恢复
      toggleNode(qu.extra);
      ans[qu.id] = distinct;
      toggleNode(qu.extra);
    } else {
      ans[qu.id] = distinct;
    }
  }

  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
  }

  return 0;
}
