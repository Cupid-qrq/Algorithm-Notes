// 混合背包基础（01+多重+完全）模板题，P1833

#include <bits/stdc++.h>
using namespace std;

string s, e;
int n;
int dp[1007], cost[10001], value[10001], cnt[10001];

int get(string s) {
  int ans = 0, temp = 0;
  for (char c : s) {
    if (c == ':') {
      ans += temp * 60;
      temp = 0;
    }
    temp = (c - '0') + temp * 10;
  }
  ans += temp;
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s >> e >> n;
  int t = get(e) - get(s);
  for (int i = 1; i <= n; i++)
    cin >> cost[i] >> value[i] >> cnt[i];

  for (int i = 1; i <= n; i++) {
    int c = cnt[i], k = 1;
    // 完全背包
    if (c == 0) {
      for (int j = 0; j <= t; j++) {
        if (j >= cost[i])
          dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
      }
    }
    // 多重背包
    else {
      while (k <= c) {
        int curcost = k * cost[i], curvalue = k * value[i];
        for (int j = t; j >= curcost; j--)
          dp[j] = max(dp[j], dp[j - curcost] + curvalue);
        c -= k;
        k <<= 1;
      }
      if (c) {
        int curcost = c * cost[i], curvalue = c * value[i];
        for (int j = t; j >= curcost; j--)
          dp[j] = max(dp[j], dp[j - curcost] + curvalue);
      }
    }
  }
  cout << dp[t];
  return 0;
}