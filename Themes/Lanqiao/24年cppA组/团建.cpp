#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> c, d;
vector<vector<int>> t1, t2;
// 预处理：每个节点的子节点按权值排序存储
vector<vector<pair<int, int>>> child_sorted; // {权值, 子节点ID}

// 直接在树2中贪心匹配path1，返回最长匹配长度
int findMaxMatch(const vector<int> &path1) {
  int node = 1;
  int len = 0;

  for (int val : path1) {
    // 检查当前节点的权值是否匹配
    if (d[node] != val) {
      return len;
    }
    len++;

    // 获取下一个权值（如果还有的话）
    int next_val_pos = len; // path1中下一个权值的位置
    if (next_val_pos >= path1.size()) {
      break; // 已经到了path1的末尾
    }

    int next_val = path1[next_val_pos];

    // 通过二分查找在子节点中找权值为next_val的
    auto &children = child_sorted[node];
    auto it =
        lower_bound(children.begin(), children.end(), make_pair(next_val, 0));

    if (it == children.end() || it->first != next_val) {
      break; // 无法继续
    }
    node = it->second;
  }

  return len;
}

// DFS遍历树1的所有根->叶路径
void dfs(int u, int parent, vector<int> &path, int &ans) {
  path.push_back(c[u]);

  bool isLeaf = true;
  for (int v : t1[u]) {
    if (v != parent) {
      isLeaf = false;
      dfs(v, u, path, ans);
    }
  }

  if (isLeaf) {
    int match_len = findMaxMatch(path);
    ans = max(ans, match_len);
  }

  path.pop_back();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  t1.resize(n + 1);
  t2.resize(m + 1);
  c.resize(n + 1);
  d.resize(m + 1);
  child_sorted.resize(m + 1);

  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= m; i++)
    cin >> d[i];

  int u, v;
  for (int i = 1; i <= n - 1; i++) {
    cin >> u >> v;
    t1[u].push_back(v);
    t1[v].push_back(u);
  }
  for (int i = 1; i <= m - 1; i++) {
    cin >> u >> v;
    t2[u].push_back(v);
    t2[v].push_back(u);
  }

  // 预处理：对树2的每个节点，把子节点按权值排序
  for (int node = 1; node <= m; node++) {
    for (int child : t2[node]) {
      child_sorted[node].push_back({d[child], child});
    }
    sort(child_sorted[node].begin(), child_sorted[node].end());
  }

  int ans = 0;
  vector<int> path;
  dfs(1, -1, path, ans);

  cout << ans << endl;
  return 0;
}
