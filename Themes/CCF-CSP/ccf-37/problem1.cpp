#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int b, c;
LL func(int x) {
  LL tmp = x * x + b * x + c;
  return tmp;
}

int main() {
  int l, r;

  cin >> b >> c >> l >> r;

  LL ans = 0;

  if (l % 2 == 1)
    l++;
  for (int i = l; i <= r; i += 2) {
    ans += func(i);
  }

  ans *= 2;

  cout << ans;

  return 0;
}