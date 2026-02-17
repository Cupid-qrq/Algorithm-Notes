#include <bits/stdc++.h>
using namespace std;

int n;

bool isvalid(int x, int y) { return x <= n && x >= 1 && y <= n && y >= 1; }

int main() {
  int k;
  cin >> n >> k;

  string s;
  int x, y;
  while (k--) {
    cin >> x >> y;
    cin >> s;
    for (char &c : s) {
      if (c == 'f' && isvalid(x, y + 1)) {
        y += 1;
      } else if (c == 'b' && isvalid(x, y - 1)) {
        y -= 1;
      } else if (c == 'l' && isvalid(x - 1, y)) {
        x -= 1;
      } else if (c == 'r' && isvalid(x + 1, y)) {
        x += 1;
      }
    }
    cout << x << " " << y << endl;
  }
  return 0;
}