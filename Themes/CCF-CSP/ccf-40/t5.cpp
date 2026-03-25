#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 3;
int n, w, q;
vector<int> num[N];
vector<bool> fire;
// reinforce solution
void query() {
  long long cost = 0;
  for (int i = 1; i <= n; i++) {
    if (fire[i])
      continue;
    int len = num[i].size();
    if (len == 1) {
      cost++;
      continue;
    }
    for (int j = 0; j < len; j++) {
      for (int k = j + 1; k < len; k++) {
      }
    }
  }
  cout << "cost: " << cost << '\n';
  return;
}

int main() {
  cin >> n >> w;
  fire.resize(n + 1, false);
  int m, cur, u, v, x, op;
  for (int i = 1; i <= n; i++) {
    cin >> m;
    for (int j = 1; j <= m; j++) {
      cin >> cur;
      num[i].push_back(cur);
    }
  }
  cin >> q;
  while (q--) {
    cin >> op;
    if (op == 1) {
      cin >> u >> x;
      num[u].push_back(x);
    } else if (op == 2) {
      cin >> u >> v;
      for (int a : num[v]) {
        num[u].push_back(a);
      }
      fire[v] = true;
    } else
      query();
  }

  return 0;
}