#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1005;
vector<vector<ll>> S(N, vector<ll>(N));
vector<vector<ll>> T(N, vector<ll>(N));
vector<int> a;

ll get(vector<ll> &arr) {
  int len = arr.size();
  if (len < 1)
    return 0;
  if (len == 1)
    return a[arr[0]];
  ll ans = a[arr[0]];
  for (int i = 1; i < len; i++) {
    ans ^= a[arr[i]];
  }
  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  a.resize(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i <= m; i++) {
    int s;
    cin >> s;
    for (int k = 1; k <= s; k++)
      cin >> S[i][k];
  }

  for (int i = 1; i <= m; i++) {
    int t;
    cin >> t;
    for (int k = 1; k <= t; k++)
      cin >> T[i][k];
  }

  for (int i = 1; i <= m; i++) {
    bool fact = (S[i] == T[i]) ? true : false;
    bool judge = (get(S[i]) == get(T[i])) ? true : false;
    //cout << "for case " << i << " : " << fact << "  " << judge << endl;
    if (fact == judge)
      cout << "correct" << '\n';
    else
      cout << "wrong" << '\n';
  }

  return 0;
}