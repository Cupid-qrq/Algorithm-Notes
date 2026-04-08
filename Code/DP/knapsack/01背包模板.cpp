// 01背包标准模板题

// 二维dp写法
// #include <bits/stdc++.h>
// using namespace std;

// int T, M;
// int cost[101], value[101];
// int dp[101][1001];

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   cin >> T >> M;
//   for (int i = 1; i <= M; i++) {
//     cin >> cost[i] >> value[i];
//   }

//   for (int i = 1; i <= M; i++) {
//     for (int j = 1; j <= T; j++) {
//       if (j >= cost[i])
//         dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i]] + value[i]);
//       else
//         dp[i][j] = dp[i - 1][j];
//     }
//   }

//   //   for (int i = 0; i <= M;i++){
//   //     for (int j = 0; j <= T;j++){
//   //       cout << dp[i][j] << " ";
//   //     }
//   //     cout << endl;
//   //   }
//   cout << dp[M][T];
//   return 0;
// }

// 一维dp写法,采用滚动数组，先遍历物品，再遍历容量，要倒序遍历容量！！！
#include <bits/stdc++.h>
using namespace std;

int T, M;
int dp[1001], cost[101], value[101];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T >> M;
  for (int i = 1; i <= M; i++) {
    cin >> cost[i] >> value[i];
  }

  for (int i = 1; i <= M; i++) {
    for (int j = T; j >= cost[i]; j--) {
      dp[j] = max(dp[j - cost[i]] + value[i], dp[j]);
    }
  }
  cout << dp[T];
  return 0;
}