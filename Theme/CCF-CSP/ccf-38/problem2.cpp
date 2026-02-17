#include <bits/stdc++.h>
using namespace std;

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int n, k;

bool isvalid(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= n; }

int main() {
  cin >> n >> k;
  int x, y;
  cin >> x >> y;
  queue<pair<int, int>> q;
  vector<vector<int>> visited(n + 1, vector<int>(n + 1, -1));
  visited[x][y] = 0;
  int cnt = 1;
  q.push({x, y});

  while (!q.empty()) {
    auto [curx, cury] = q.front();
    q.pop();

    if (visited[curx][cury] == k)
      continue;

    for (int i = 0; i < 8; i++) {
      int nx = curx + dx[i], ny = cury + dy[i];
      if (isvalid(nx, ny) && visited[nx][ny] == -1) {
        visited[nx][ny] = visited[curx][cury] + 1;
        cnt++;
        q.push({nx, ny});
      }
    }
  }

  cout << cnt;

  return 0;
}