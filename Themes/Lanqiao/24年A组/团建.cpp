#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<int> c, d;
vector<vector<int>> g1, g2;
vector<vector<int>> ch1, ch2;

void build_tree1(int u, int parent) {
  for (int v : g1[u]) {
    if (v == parent)
      continue;
    build_tree1(v, u);
    ch1[u].push_back(v);
  }
  sort(ch1[u].begin(), ch1[u].end(), [&](int a, int b) { return c[a] < c[b]; });
}

void build_tree2(int u, int parent) {
  for (int v : g2[u]) {
    if (v == parent)
      continue;
    build_tree2(v, u);
    ch2[u].push_back(v);
  }
  sort(ch2[u].begin(), ch2[u].end(), [&](int a, int b) { return d[a] < d[b]; });
}

int solve(int u, int v) {
  // 当前 u,v 权值已相等，至少可以匹配这一层。
  int best = 1;

  const auto &a = ch1[u];
  const auto &b = ch2[v];
  int i = 0, j = 0;

  // 两个有序孩子表按权值做交集，匹配到相同权值时递归向下。
  while (i < (int)a.size() && j < (int)b.size()) {
    int w1 = c[a[i]];
    int w2 = d[b[j]];
    if (w1 == w2) {
      best = max(best, 1 + solve(a[i], b[j]));
      i++;
      j++;
    } else if (w1 < w2) {
      i++;
    } else {
      j++;
    }
  }

  return best;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  c.assign(n + 1, 0);
  d.assign(m + 1, 0);
  g1.assign(n + 1, {});
  g2.assign(m + 1, {});
  ch1.assign(n + 1, {});
  ch2.assign(m + 1, {});

  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= m; i++)
    cin >> d[i];

  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g1[u].push_back(v);
    g1[v].push_back(u);
  }
  for (int i = 1; i <= m - 1; i++) {
    int u, v;
    cin >> u >> v;
    g2[u].push_back(v);
    g2[v].push_back(u);
  }

  build_tree1(1, 0);
  build_tree2(1, 0);

  if (c[1] != d[1]) {
    cout << 0;
    return 0;
  }

  cout << solve(1, 1);

  return 0;
}

/*
Trie 解法

一、Trie 在这题里表示什么
1. Trie 的一条“根到某节点路径”表示一个权值序列前缀。
2. 我们把第一棵树从根出发的所有前缀都插入 Trie。
3. 然后在第二棵树里从根 DFS，同时在 Trie 里按权值尝试转移：
   - 能转移：说明这个前缀在第一棵树里也存在，公共前缀长度 +1
   - 不能转移：说明这条分支到此为止
4. DFS 过程中的最大深度就是答案。

二、为什么这样是对的
1. 两人得分是“根到叶路径序列”的最长公共前缀。
2. 只要某个前缀存在于两棵树，就能继续尝试下一层。
3. Trie 恰好就是“前缀是否存在”的高效结构。

三、复杂度
1. 插入第一棵树：O(n)
2. 匹配第二棵树：O(m)
3. 总体：O(n + m)（哈希转移均摊 O(1)）

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
  // key: 下一层结点权值，value: Trie 子节点编号
  unordered_map<int, int> nxt;
};

int n, m;
vector<int> c, d;
vector<vector<int>> g1, g2;
vector<TrieNode> trie;
int ans = 0;

// 把第一棵树的所有“根到当前点”的前缀路径插入 Trie。
// node 是当前前缀对应的 Trie 节点编号。
void insert_dfs(int u, int parent, int node) {
  for (int v : g1[u]) {
    if (v == parent)
      continue;
    int w = c[v];
    int to;
    auto it = trie[node].nxt.find(w); // 看 Trie 当前节点能否转移到权值 w
    // 如果不能转移，说明这个前缀之前没出现过，需要新建一个 Trie 节点。
    if (it == trie[node].nxt.end()) { 
      to = (int)trie.size(); // 新 Trie 节点编号就是当前 Trie 大小
      trie[node].nxt[w] = to; // 在当前 Trie 节点上记录转移到权值 w 的边
      trie.push_back({}); // 新建 Trie 节点
    } else {
      to = it->second; // 已经存在转移，直接复用
    }
    // 继续把孩子子树对应的前缀插入。
    insert_dfs(v, u, to);
  }
}

// 在第二棵树上 DFS，并在 Trie 上同步走。
// depth 表示当前已经匹配到的公共前缀长度。
void match_dfs(int u, int parent, int node, int depth) {
  ans = max(ans, depth);
  for (int v : g2[u]) {
    if (v == parent)
      continue;
    int w = d[v];
    auto it = trie[node].nxt.find(w);
    if (it != trie[node].nxt.end()) {
      // Trie 能转移，说明前缀还能延长。
      match_dfs(v, u, it->second, depth + 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  c.assign(n + 1, 0);
  d.assign(m + 1, 0);
  g1.assign(n + 1, {});
  g2.assign(m + 1, {});

  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= m; i++)
    cin >> d[i];

  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g1[u].push_back(v);
    g1[v].push_back(u);
  }
  for (int i = 1; i <= m - 1; i++) {
    int u, v;
    cin >> u >> v;
    g2[u].push_back(v);
    g2[v].push_back(u);
  }

  if (c[1] != d[1]) {
    // 根权值都不同，公共前缀长度只能是 0。
    cout << 0;
    return 0;
  }

  // 建 Trie：先放一个空根节点（表示“还没走任何权值”）。
  trie.reserve(n + 5);
  trie.push_back({});
  insert_dfs(1, 0, 0);

  // 两棵树根权值已相等，初始公共前缀长度至少为 1。
  ans = 1;
  match_dfs(1, 0, 0, 1);
  cout << ans;

  return 0;
}
*/