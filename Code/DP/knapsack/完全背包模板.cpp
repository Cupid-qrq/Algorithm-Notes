// 完全背包模板，洛谷P1616

// 先遍历物品，再遍历容量，正序遍历容量！！！因为可以无限拿
#include <bits/stdc++.h>
using namespace std;

int t, m;
const int N = 1e7 + 5;
long long dp[N], cost[N], value[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> t >> m;
  for (int i = 1; i <= m; i++) {
    cin >> cost[i] >> value[i];
  }

  for (int i = 1; i <= m; i++) {
    for (int j = cost[i]; j <= t; j++) {
      dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
    }
  }

  //   for (int i = 0; i <= t; i++)
  //     cout << dp[i] << " ";
  cout << dp[t];
  return 0;
}