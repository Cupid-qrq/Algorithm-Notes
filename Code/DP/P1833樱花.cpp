// 2026.2.25
// tag: DP 多重背包，完全背包

/* 当一件物品只有取或不取的时候，为01背包问题
这个时候先遍历物品，再遍历背包容量，且背包容量要从大到小遍历

vector<int> dp(total + 1, 0);
for (int i = 1; i <= n; i++) {
  for (int v = total; v >= cost[i]; v--) {
    dp[v] = max(dp[v], dp[v - cost[i]] + value[i]);
  }
}

当一件物品可以取无限多次的时候，为完全背包问题
这个时候先遍历物品，再遍历背包容量，且背包容量要从小到大遍历
这是因为算dp[v]时，dp[v - cost[i]]已经被更新过了，可以继续使用这个物品

vector<int> dp(total + 1, 0);
for (int i = 1; i <= n; i++) {
  for (int v = cost[i]; v <= total; v++) {
    dp[v] = max(dp[v], dp[v - cost[i]] + value[i]);
  }
}

当一件物品有次数限制的时候，为多重背包问题
这个时候先遍历物品，再遍历背包容量，且背包容量要从大到小遍历
这是因为从大到小遍历背包容量时，dp[v - cost[i]]还没有被更新过，可以继续使用这个物品

vector<int> dp(total + 1, 0);
for (int i = 1; i <= n; i++) {
  for (int k = 1; k <= cnt[i]; k++) {
    for (int v = total; v >= cost[i]; v--) {
      dp[v] = max(dp[v], dp[v - cost[i]] + value[i]);
    }
  }
}


 */
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int h1, h2, m1, m2;
  int n;
  char c;
  cin >> h1 >> c >> m1;
  cin >> h2 >> c >> m2;
  cin >> n;
  int total = max(h2 - 1, 0) * 60 + m2 - max(h1 - 1, 0) * 60 - m1;

  vector<int> value(n + 1), cost(n + 1), cnt(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> cost[i] >> value[i] >> cnt[i];
  }

  // dp[i] 表示前i时间内能得到的最大值
  vector<int> dp(total + 1, 0);

  for (int i = 1; i <= n; i++) {
    if (cnt[i]) { // 如果有次数限制，则为多重背包
      for (int k = 1; k <= cnt[i]; k++) {
        for (int v = total; v >= cost[i]; v--) {
          dp[v] = max(dp[v], dp[v - cost[i]] + value[i]);
        }
      }
    } else { // 没有次数限制，则为完全背包
      for (int v = cost[i]; v <= total; v++) {
        dp[v] = max(dp[v], dp[v - cost[i]] + value[i]);
      }
    }
  }

  //   for (int x : dp) {
  //     cout << x << " ";
  //   }
  cout << dp[total];
  return 0;
}