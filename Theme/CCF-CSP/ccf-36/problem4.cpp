#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n + 1), k(n + 1);
  a[0] = k[0] = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> k[i];

  vector<int> memo(n + 1, -1);
  memo[1] = 0;
  queue<int> q;
  q.push(1);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (cur == n) {
      cout << memo[n];
      return 0;
    }

    for (int i = 1; i <= k[cur]; i++) {
      int np = cur + i;
      if (np > n)
        break;
      int next = np - a[np];
      if (memo[next] == -1) {
        memo[next] = memo[cur] + 1;
        q.push(next);
      }
    }
  }

  cout << -1;

  return 0;
}
