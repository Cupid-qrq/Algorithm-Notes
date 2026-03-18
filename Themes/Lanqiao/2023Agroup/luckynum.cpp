#include <bits/stdc++.h>
using namespace std;

int get(int x) {
  int sum = 0;
  while (x > 0) {
    sum += x % 10;
    x /= 10;
  }
  return sum;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int sum = 0;
  for (int i = 10; i <= 99; i++) {
    if (i / 10 == i % 10)
      sum++;
  }

  for (int i = 1000; i <= 9999; i++) {
    int h = i / 100, l = i % 100;
    if (get(h) == get(l))
      sum++;
  }
  for (int i = 100000; i <= 999999; i++) {
    int h = i / 1000, l = i % 1000;
    if (get(h) == get(l))
      sum++;
  }
  for (int i = 10000000; i <= 99999999; i++) {
    int h = i / 10000, l = i % 10000;
    if (get(h) == get(l))
      sum++;
  }
  cout << sum;

  return 0;
}