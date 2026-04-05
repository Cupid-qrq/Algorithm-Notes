#include <bits/stdc++.h>
using namespace std;

int t, n, m;
unordered_map<int, int> freq;
set<pair<int, int>> memo;
vector<int> nums;
long long ans;
long long base = 1;
const int mod = 1000000007;

vector<long long> fact, invfact;

// 快速幂
long long qpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

int main() {
  cin >> t;
  nums.resize(t);
  fact.resize(t + 1);
  invfact.resize(t + 1);

  // 预处理阶乘
  fact[0] = 1;
  for (int i = 1; i <= t; i++) {
    fact[i] = fact[i - 1] * i % mod;
  }

  // 预处理逆元阶乘
  invfact[t] = qpow(fact[t], mod - 2);
  for (int i = t - 1; i >= 0; i--) {
    invfact[i] = invfact[i + 1] * (i + 1) % mod;
  }

  // 输入 + 统计频率
  for (int i = 0; i < t; i++) {
    cin >> nums[i];
    freq[nums[i]]++;
  }

  // 所有频率对应的 invfact 先统一乘一遍，后面每个候选只做常数修正。
  for (auto [num, f] : freq) {
    base = base * invfact[f] % mod;
  }

  // 枚举 n
  for (int i = 0; i < t; i++) {
    n = nums[i];

    if ((t - 2) % n != 0)
      continue;

    m = (t - 2) / n;

    if (memo.count({n, m}))
      continue;

    if (!freq.count(m))
      continue;

    // 检查是否能取出 n 和 m
    if (n == m && freq[n] < 2)
      continue;
    if (n != m && (freq[n] < 1 || freq[m] < 1))
      continue;

    long long curans = fact[n * m] * base % mod;
    if (n == m) {
      curans = curans * freq[n] % mod * (freq[n] - 1) % mod;
    } else {
      curans = curans * freq[n] % mod * freq[m] % mod;
    }

    ans = (ans + curans) % mod;
    memo.insert({n, m});
  }

  cout << ans % mod;

  return 0;
}