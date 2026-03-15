#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main() {
  int cnt = 0;
  for (int i = 1; i <= 20250412; i++) {
    vector<int> c(10, 0);
    int cur = i;
    while (cur > 0) {
      c[cur % 10]++;
      cur /= 10;
    }
    if (c[0] == 1 && c[2] == 2 && c[5] == 1)
      cnt++;
  }
  cout << cnt;
  return 0;
}