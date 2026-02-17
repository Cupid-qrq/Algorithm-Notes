#include <bits/stdc++.h>
using namespace std;

int main() {
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int m, s, n;
    cin >> m >> s >> n;
    double z = 1.0 * (n - m) / s;
    z = round(z * 100);
    int x = z;
    int x2 = x / 10 + 1;
    int y2 = x % 10 + 1;
    cout << x2 << " " << y2 << endl;
  }
  return 0;
}