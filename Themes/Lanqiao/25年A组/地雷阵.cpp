#include <bits/stdc++.h>
#include <cmath>
using namespace std;
const long double pi = acosl(-1.0L);
using ld = long double;
int n;
vector<pair<ld, ld>> rs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  ld x, y, r;
  while (n--) {
    cin >> x >> y >> r;
    ld d = hypotl(x, y);
    ld theta = atan2l(y, x);
    ld epslion = asinl(min<ld>(1.0L, r / d));
    ld left = theta - epslion;
    ld right = theta + epslion;

    if (left < right) {
      rs.push_back({left, right});
    }
  }

  sort(rs.begin(), rs.end(), [](const pair<ld, ld> &a, const pair<ld, ld> &b) {
    return a.first < b.first;
  });

  ld covered = 0.0L;
  ld cur_l = 0.0L, cur_r = 0.0L;
  bool has = false;

  for (const auto &[l, r] : rs) {
    if (!has) {
      cur_l = l;
      cur_r = r;
      has = true;
      continue;
    }

    if (l <= cur_r) {
      cur_r = max(cur_r, r);
    } else {
      covered += cur_r - cur_l;
      cur_l = l;
      cur_r = r;
    }
  }

  if (has) {
    covered += cur_r - cur_l;
  }

  ld ans = 1.0L - covered / (pi / 2);
  cout << fixed << setprecision(3) << ans;

  return 0;
}