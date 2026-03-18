#include <bits/stdc++.h>
using namespace std;

// 40分解法
/*
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.size();
  int ans = 0;
  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (s[r] > s[l])
        continue;
      else {
        string cur = s;
        reverse(cur.begin() + l, cur.begin() + r + 1);
        if (cur < s) {
          ans++;
          //cout << l << " " << r << " " << cur << '\n';
        }
      }
    }
  }

  cout << ans;
  return 0;
}
*/

// AC solution: 区间dp
int dp[5001][5001];

int main() {
  string s;
  cin >> s;
  int n = s.size();
  int ans = 0;
  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (s[r] > s[l])
        dp[l][r]=0;
      else if (s[r] == s[l]) {
        dp[l][r] = dp[l + 1][r - 1];
      } else
        dp[l][r] = 1;
      ans += dp[l][r];
    }
  }

  cout << ans;
  return 0;
}