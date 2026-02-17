#include <bits/stdc++.h>
using namespace std;

// int main() {
//   int n, m;
//   cin >> n >> m;

//   vector<int> profit(m, 0);
//   for (int i = 0; i < m; i++)
//     cin >> profit[i];

//   double max_ave = 0.0;
//   int index = -1;
//   for (int i = 0; i < m; i++) {
//     double tmp = profit[i] / (i + 1);
//     max_ave = max(max_ave, tmp);
//     if (max_ave == tmp)
//       index = i + 1;
//   }

//   long long integral = n / index;
//   int k = n % index;
//   long long ans = integral * profit[index - 1] + profit[k - 1];
//   cout << ans;
//   return 0;
// }

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> profit(m + 1, 0);
  for (int i = 1; i <= m; i++)
    cin >> profit[i];

  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (j > i)
        continue;
      dp[i] = max(dp[i], dp[i - j] + profit[j]);
    }
  }

  cout << dp[n];

  return 0;
}