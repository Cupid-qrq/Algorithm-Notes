#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, s;
  cin >> n >> s;
  vector<ll> p(n), c(n);
  ll totalP = 0;
  for (int i = 0; i < n; i++) {
    cin >> p[i] >> c[i];
    totalP += p[i];
  }

  // 按 c_i 从小到大排序
  vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&](int a, int b) { return c[a] < c[b]; });

  // 后缀和：suffP[i] = sum of p[idx[i..n-1]], suffCP[i] = sum of c[j]*p[j] for
  // j=idx[i..n-1]
  vector<ll> suffP(n + 1, 0), suffCP(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    suffP[i] = suffP[i + 1] + p[idx[i]];
    suffCP[i] = suffCP[i + 1] + c[idx[i]] * p[idx[i]];
  }

  ll groupCost = min(s, totalP); // 一次团训的实际花费
  ll ans = suffCP[0];            // k=0：全部单训

  // 枚举团训次数 k = c[idx[i]] for each i, 以及 k = c[idx[n-1]]（即max_c）
  // 对于团训 k 次：cost = k * groupCost + sum_{c_j > k} (c_j - k) * p_j
  // 其中 sum_{c_j > k} (c_j - k)*p_j = suffCP[pos] - k * suffP[pos]
  // pos 是第一个 c[idx[pos]] > k 的位置
  for (int i = 0; i < n; i++) {
    ll k = c[idx[i]];
    // c[idx[i]] == k 的士兵刚好满足，不需要单训补
    // 第一个 c > k 的位置是 upper_bound
    int pos = upper_bound(idx.begin(), idx.end(), k,
                          [&](ll val, int id) { return val < c[id]; }) -
              idx.begin();
    ll cost = k * groupCost + suffCP[pos] - k * suffP[pos];
    ans = min(ans, cost);
  }

  cout << ans;
  return 0;
}