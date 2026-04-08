#include <bits/stdc++.h>
using namespace std;

long long dp[31][10];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  dp[0][0] = 1;
  for (int i = 1; i <= 30; i++) {
    for (long long t : dp[i - 1])
      dp[i][0] += t;
    for (int j = 1; j < 10; j++) {
      dp[i][j] = dp[i - 1][j - 1];
    }
  }

//   for (int i = 0; i <= 30; i++) {
//     for (int j = 0; j <= 10; j++) {
//       cout << dp[i][j] << "\t";
//     }
//     cout << '\n';
//   }

  long long ans = 0;
  for (int i = 0; i <= 30; i++)
    ans += dp[i][7];
  cout << ans;
  return 0;
}