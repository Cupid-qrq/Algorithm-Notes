#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const long long MOD = 998244353;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
  int n;
  cin >> n;

  vector<int> num(n);
  for (int i = 0; i < n; i++)
    cin >> num[i];

  // 动态规划表 dp[i][j] 表示子数组 [i, j] 的 GCD
  vector<vector<LL>> dp(n, vector<LL>(n));

  // 初始化 dp 表
  for (int i = 0; i < n; i++) {
    dp[i][i] = num[i]; // 单个元素的 GCD 就是它本身
    for (int j = i + 1; j < n; j++) {
      dp[i][j] = gcd(dp[i][j - 1], num[j]); // 利用递推关系计算 GCD
    }
  }

  LL ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      LL tmp = (i + 1) * (j + 1) % MOD;
      tmp = tmp * dp[i][j] % MOD;
      ans = (ans + tmp) % MOD;
    }
  }

  cout << ans;
  return 0;
}