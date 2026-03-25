#include <bits/stdc++.h>
using namespace std;

vector<int> k, a;

int f(int x, int k) { return ((x * x + k * k) % 8) ^ k; }

int g(int x, int k) {
  int a, b, c, ans = 0;
  c = 0x7 & x;
  b = (0x38 & x) >> 3;
  a = (0x1C0 & x) >> 6;

  int mask1 = a ^ f(c, k), mask2 = c ^ f(b, k);
  //   cout << a << " " << b << " " << c << endl;
  //   cout << mask1 << " " << mask2 << endl;
  ans = ans | mask1;
  ans = ans | (mask2 << 3);
  ans = ans | (b << 6);
  //   cout << ans;
  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;

  k.resize(m + 1, 0);
  a.resize(n + 1, 0);
  for (int i = 1; i <= m; i++)
    cin >> k[i];
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  vector<int> memo(1000, 0);
  for (int i = 1; i <= n; i++) {
    if (memo[a[i]]) {
      cout << memo[a[i]] << " ";
      continue;
    }
    for (int f = 0; f <= 1e5; f++) {
      int curf = f, nextf = 0;
      for (int j = 1; j <= m; j++) {
        nextf = g(curf, k[j]);
        curf = nextf;
      }
      if (curf == a[i]) {
        cout << f << " ";
        memo[a[i]] = f;
        break;
      }
    }
  }

  return 0;
}