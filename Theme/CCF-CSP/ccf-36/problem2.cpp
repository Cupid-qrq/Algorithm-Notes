#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 0; i <= n; i++)
    cin >> a[i];

  vector<int> b(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> b[i];

  // s[i]表示到到第i个位置时所需的最小花费
  vector<int> s(n + 1);
  s[0] = a[0];
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i] - b[i];
  }

  vector<int> premax(n + 1);
  premax[0] = s[0];
  for (int i = 1; i <= n; i++) {
    premax[i] = max(s[i], premax[i - 1]);
  }

  vector<int> sufmax(n + 1);
  sufmax[n] = s[n];
  for (int i = n - 1; i >= 0; i--) {
    sufmax[i] = max(s[i], sufmax[i + 1]);
  }

  for (int m = 1; m <= n; m++) {
    cout << max(premax[m - 1], sufmax[m] + b[m]) << " ";
  }
  return 0;
}