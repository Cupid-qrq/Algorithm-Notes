// 分组背包模板，每组物品只能选一个，求最大价值
// 核心在于先遍历每个组，然后必须先倒序遍历背包容量，最后遍历组内物品
// 为什么需要先倒序背包容量再遍历组内物品？因为每组只能选一个，如果先正序遍历背包容量，那么在更新 dp[j] 时，可能会用到已经更新过的 dp[j - cost[k]]，导致同一组内的物品被重复选取。

// 如果是分组完全背包，那么就只需要遍历组->正序遍历背包容量->组内物品即可，因为每组内物品可以重复选取，不会有同一组内物品被重复选取的问题。

#include <bits/stdc++.h>
using namespace std;

int n, m;
int dp[1007], cost[1007], value[1007];
vector<int> group[1007];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    int g;
    cin >> cost[i] >> value[i] >> g;
    group[g].push_back(i);
  }

  for (auto &gp : group) {
    for (int j = m; j >= 0; j--) {
      for (int k : gp) {
        if (j >= cost[k])
          dp[j] = max(dp[j], dp[j - cost[k]] + value[k]);
      }
    }
  }

  cout << dp[m];

  return 0;
}