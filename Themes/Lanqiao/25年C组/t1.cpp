#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int cnt = 0;
  for (int num = 1; num <= 202504; num++) {
    int sum = 0, d = num;
    while (d > 0) {
      sum += (d % 10);
      d /= 10;
    }
    if (sum % 5 == 0)
      cnt++;
  }
  cout << cnt;
  return 0;
}