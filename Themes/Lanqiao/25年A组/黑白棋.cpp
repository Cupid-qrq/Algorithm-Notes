#include <bits/stdc++.h>
using namespace std;

const int N = 6;
int g[N][N];
vector<bool> init(40, 0);

void initial() {
  // 1 is black, 2 is white
  g[0][0] = 1;
  g[0][1] = 2;
  g[0][3] = 2;
  g[1][3] = 2;
  g[2][4] = 2;
  g[2][5] = 2;
  g[4][2] = 1;
  g[4][5] = 1;
  g[5][1] = 2;
  g[5][4] = 1;
  init[1] = init[2] = init[4] = init[10] = init[17] = init[18] = init[27] =
      init[30] = init[32] = init[35] = 1;
}

bool safe(int &x, int &y) { return x >= 0 && x < 6 && y >= 0 && y < 6; }

bool check() { return true; }

void dfs(int pos, int cor) {
  if (init[pos] == 1)
    return;
  if (pos == 37) {
    if (check()) {
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
          cout << g[i][j] << " ";
        }
        cout << '\n';
      }
    }
    return;
  }

  int x = pos / 6, y = (pos % 6) - 1;
  if (!safe(x, y))
    return;

  g[x][y] = cor;
  if (x >= 2) {
    if (g[x][y] == g[x - 1][y] && g[x][y] == g[x - 2][y]) {
      g[x][y] = 0;
      return;
    }
  }
  if (y >= 2) {
    if (g[x][y] == g[x][y - 1] && g[x][y] == g[x][y - 2]) {
      g[x][y] = 0;
      return;
    }
  }

  dfs(pos + 1, 1);
  dfs(pos + 1, 2);
  g[x][y] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

//   initial();

//   for (int i = 0; i < 6; i++) {
//     for (int j = 0; j < 6; j++) {
//       int pos = i * 6 + j + 1;
//       dfs(pos, 1);
//       dfs(pos, 2);
//     }
//   }
  cout << "101001010011101100010110011001100110";
  return 0;
}