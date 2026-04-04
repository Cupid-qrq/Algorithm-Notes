#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<ll> a, pref;
ll n, m, mod;

ll change(ll a, ll b) {
  ll ans = 0, pos = 1;
  while (a > 0 || b > 0) {
    ans += ((a %mod) + (b %mod)) % mod * pos;
    a /= mod;
    b /= mod;
    pos *= mod;
  }
  return ans;
}   

ll f(ll x, ll stop) {
  if (x == stop)
    return x;
  return change(x, f(x - 1, stop));
}

void query(ll l, ll r) {
  ll ans = pref[l];
  for (int i = l + 1; i <= r; i++) {
    ans = change(ans, pref[i]);
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> mod;
  a.resize(n + 1, 0);
  pref.resize(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pref[i] = f(a[i], a[i] - a[i] % mod);
  }

  int op, l, r, v;
  while (m--) {
    cin >> op;
    if (op == 1) {
      cin >> l >> r >> v;
      for (int i = l; i <= r; i++) {
        a[i] = change(a[i], v);
        pref[i] = f(a[i], a[i] - a[i] % mod);
      }
    } else {
      cin >> l >> r;
      query(l, r);
    }
  }

  return 0;
}
