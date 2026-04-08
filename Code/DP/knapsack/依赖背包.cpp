// P1064, 主件-附件

#include <bits/stdc++.h>
using namespace std;

int n, m;
int dp[32010], cost[61], imp[61], q[61];
vector<int> group[61];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> cost[i] >> imp[i] >> q[i];
    group[q[i]].push_back(i);
  }

  // 只以主件（q[i] == 0）为组做分组背包。
  for (int i = 1; i <= m; i++) {
    if (q[i] != 0)
      continue;

    // 主件 i 的附件编号列表。
    const auto &att = group[i];

    // 预先算好该组的合法购买方案（必须包含主件）。
    vector<pair<int, int>> opts;
    int c0 = cost[i], v0 = cost[i] * imp[i];
    opts.push_back({c0, v0}); // 只买主件

    if (att.size() >= 1) {
      int a = att[0];
      opts.push_back({c0 + cost[a], v0 + cost[a] * imp[a]}); // 主件+附件1
    }
    if (att.size() >= 2) {
      int b = att[1];
      opts.push_back({c0 + cost[b], v0 + cost[b] * imp[b]}); // 主件+附件2
      int a = att[0];
      opts.push_back({c0 + cost[a] + cost[b],
                      v0 + cost[a] * imp[a] + cost[b] * imp[b]}); // 全买
    }

    // 分组背包：每组最多选一个方案，容量倒序。
    for (int j = n; j >= 0; j--) {
      for (auto &op : opts) {
        int cc = op.first, vv = op.second;
        if (j >= cc)
          dp[j] = max(dp[j], dp[j - cc] + vv);
      }
    }
  }

  cout << dp[n];

  return 0;
}