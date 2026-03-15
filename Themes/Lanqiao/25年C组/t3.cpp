#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int g[101][101];
int cir[4] = {2, 0, 2, 5};
int main() {
  int h, w;
  cin >> h >> w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      g[i][j] = cir[((j % 4) + i) % 4];
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cout << g[i][j] << " ";
    }
    cout << '\n';
  }

  return 0;
}