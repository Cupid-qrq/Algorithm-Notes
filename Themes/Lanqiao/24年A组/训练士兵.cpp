#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;
using ll = long long;
struct cost {
  int price, cnt;
};

ll n, s, ans, total;
vector<cost> cs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> s;

  for (int i = 1; i <= n; i++) {
    int p, tmp;
    cin >> p >> tmp;
    total += p;
    cs.push_back({p, tmp});
  }

  // 次数按照升序
  sort(cs.begin(), cs.end(),
       [](const cost &a, const cost &b) { return a.cnt < b.cnt; });

  int precnt = 0;
  for (int i = 0; i < n;) {
    int curcnt = cs[i].cnt;
    ll group_sum = 0;
    int j = i;
    while (j < n && cs[j].cnt == curcnt) {
      group_sum += cs[j].price;
      j++;
    }

    if (curcnt > precnt) {
      ans += min(total, s) * 1LL * (curcnt - precnt);
    }
    total -= group_sum;
    precnt = curcnt;
    i = j;
  }

  cout << ans;
  return 0;
}