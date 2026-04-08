// 多重背包+完全背包的应用，P2851

#include <bits/stdc++.h>
using namespace std;

int n, t;
const int MAX = 6e4;
vector<int> dp1, dp2;
int value[101], cnt[101];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> t;
  dp1.assign(t + MAX + 7, 1e9);
  dp2.assign(t + MAX + 7, 1e9);
  dp1[0] = dp2[0] = 0;
  for (int i = 1; i <= n; i++)
    cin >> value[i];
  for (int i = 1; i <= n; i++)
    cin >> cnt[i];

  for (int i = 1; i <= n; i++) {
    int c = cnt[i], k = 1;
    while (k <= c) {
      int curv = k * value[i];
      for (int j = t + MAX; j >= curv; j--)
        dp1[j] = min(dp1[j], dp1[j - curv] + k);
      c -= k;
      k <<= 1;
    }
    if (c) {
      int curv = c * value[i];
      for (int j = t + MAX; j >= curv; j--)
        dp1[j] = min(dp1[j], dp1[j - curv] + c);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = value[i]; j <= t + MAX; j++)
      dp2[j] = min(dp2[j], dp2[j - value[i]] + 1);
  }

  const int INF = 1e9;
  int ans = INF;
  for (int i = t; i <= t + MAX; i++) {
    if (dp1[i] < INF && dp2[i - t] < INF) {
      ans = min(ans, dp1[i] + dp2[i - t]);
    }
  }
  if (ans == INF)
    cout << -1;
  else
    cout << ans;

  return 0;
}