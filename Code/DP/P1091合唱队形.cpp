// 2026.2.26
// tag: DP 最长上升+下降子序列

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> h(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }
  int ans = 1;
  vector<int> up(n, 1), down(n, 1);
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < i; k++) {
      if (h[k] < h[i])
        up[i] = max(up[i], up[k] + 1);
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int k = i; k < n; k++) {
      if (h[k] < h[i])
        down[i] = max(down[i], down[k] + 1);
    }
  }

  for (int i = 0; i < n; i++)
    ans = max(ans, up[i] + down[i] - 1);

  cout << n - ans;

  return 0;
}
