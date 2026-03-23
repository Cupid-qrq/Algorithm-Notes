#include <bits/stdc++.h>
using namespace std;

const int N = 307;
int n, s;
vector<pair<int, int>> tree[N];
vector<int> diameter;
vector<long long> branch(N);
vector<bool> inD(N);

void getd() {
  vector<long long> dist(n + 1, -1);
  vector<int> pre(n + 1, -1);
  queue<int> q;

  q.push(1);
  dist[1] = 0;

  int head = -1;
  long long maxd = -1;

  // 第一次 BFS
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    if (dist[cur] > maxd) {
      head = cur;
      maxd = dist[cur];
    }
    for (auto &nt : tree[cur]) {
      if (dist[nt.first] == -1) {
        dist[nt.first] = dist[cur] + nt.second;
        q.push(nt.first);
      }
    }
  }

  // 第二次 BFS
  fill(dist.begin(), dist.end(), -1);
  q.push(head);
  dist[head] = 0;
  maxd = -1;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    if (dist[cur] > maxd) {
      head = cur;
      maxd = dist[cur];
    }
    for (auto &nt : tree[cur]) {
      if (dist[nt.first] == -1) {
        dist[nt.first] = dist[cur] + nt.second;
        pre[nt.first] = cur;
        q.push(nt.first);
      }
    }
  }

  // 还原直径
  diameter.push_back(head);
  inD[head] = true;
  while (pre[head] != -1) {
    diameter.push_back(pre[head]);
    head = pre[head];
    inD[head] = true;
  }
}

// 只往非直径方向 DFS
void dfs(int start, int cur, int fa, long long dis) {
  branch[start] = max(branch[start], dis);

  for (auto &[nt, w] : tree[cur]) {
    if (nt == fa || inD[nt])
      continue;
    dfs(start, nt, cur, dis + w);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> s;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    tree[u].push_back({v, w});
    tree[v].push_back({u, w});
  }

  // 初始化
  fill(branch.begin(), branch.end(), 0);

  // 求直径
  getd();
  reverse(diameter.begin(), diameter.end());

  // 每个直径点求最大旁枝
  for (int node : diameter) {
    dfs(node, node, -1, 0);
  }

  int sz = diameter.size();

  // 前缀和：直径距离
  vector<long long> pre(sz, 0);
  for (int i = 1; i < sz; i++) {
    int u = diameter[i - 1], v = diameter[i];
    for (auto &[to, w] : tree[u]) {
      if (to == v) {
        pre[i] = pre[i - 1] + w;
        break;
      }
    }
  }

  // 滑动窗口 + 单调队列
  deque<int> dq;
  long long ans = LLONG_MAX;

  for (int l = 0, r = 0; r < sz; r++) {
    int nodeR = diameter[r];
    // 维护单调递减队列
    while (!dq.empty() && branch[nodeR] >= branch[diameter[dq.back()]])
      dq.pop_back();
    dq.push_back(r);

    // 收缩窗口
    while (pre[r] - pre[l] > s) {
      if (dq.front() == l)
        dq.pop_front();
      l++;
    }

    // 更新答案
    ans = min(
        ans, max({pre[l], pre[sz - 1] - pre[r], branch[diameter[dq.front()]]}));
  }

  cout << ans;
  return 0;
}