#include <bits/stdc++.h>
using namespace std;

int n, m;
char c[10][10];
int g[10][10]; // black is 1, white is 2
int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1},
    dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
bool found = false;
bool safe(int x, int y) { return x < n && x >= 0 && y < m && y >= 0; }

bool check(int x, int y) {
  if (c[x][y] == '_')
    return true;
  int cnt = 0, total = c[x][y] - '0';

  for (int i = 0; i < 9; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (safe(nx, ny) && g[nx][ny] == 1)
      cnt++;
    if (cnt > total)
      return false;
  }
  return cnt == total;
}

// 约束可行性剪枝：
// 已放黑数不能超过目标；已放黑数 + 未确定数 不能小于目标。
bool check_bound(int x, int y) {
  if (c[x][y] == '_')
    return true;

  int black = 0, undecided = 0, total = c[x][y] - '0';
  for (int i = 0; i < 9; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (!safe(nx, ny))
      continue;
    if (g[nx][ny] == 1)
      black++;
    else if (g[nx][ny] == 0)
      undecided++;
  }

  if (black > total)
    return false;
  if (black + undecided < total)
    return false;
  return true;
}

// 只检查受当前点影响的 3x3 中心约束（最多 9 个），常数很小。
bool local_ok(int x, int y) {
  for (int cx = x - 1; cx <= x + 1; cx++) {
    for (int cy = y - 1; cy <= y + 1; cy++) {
      if (safe(cx, cy) && !check_bound(cx, cy))
        return false;
    }
  }
  return true;
}

void print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == 2)
        cout << 0;
      else
        cout << g[i][j];
    }
    cout << '\n';
  }
}

void dfs(int pos) {
  if (found)
    return;
  if (pos == n * m) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (!check(i, j))
          return;
    print();
    found = true;
    return;
  }
  int x = pos / m, y = pos % m;
  if (!safe(x, y))
    return;

  g[x][y] = 1;
  if (local_ok(x, y)) {
    dfs(pos + 1);
  }
  g[x][y] = 2;
  if (local_ok(x, y)) {
    dfs(pos + 1);
  }
  g[x][y] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> c[i][j];

  dfs(0);

  return 0;
}