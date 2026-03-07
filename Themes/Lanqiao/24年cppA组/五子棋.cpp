#include <bits/stdc++.h>
using namespace std;

int b[5][5]; // 0=空, 1=白, 2=黑
long long ans = 0;

// 检查是否有五连子（赢棋）
bool hasWin() {
  // 检查行
  for (int i = 0; i < 5; i++) {
    if (b[i][0] != 0 && b[i][0] == b[i][1] && b[i][1] == b[i][2] &&
        b[i][2] == b[i][3] && b[i][3] == b[i][4])
      return true;
  }
  // 检查列
  for (int j = 0; j < 5; j++) {
    if (b[0][j] != 0 && b[0][j] == b[1][j] && b[1][j] == b[2][j] &&
        b[2][j] == b[3][j] && b[3][j] == b[4][j])
      return true;
  }
  // 检查主对角线
  if (b[0][0] != 0 && b[0][0] == b[1][1] && b[1][1] == b[2][2] &&
      b[2][2] == b[3][3] && b[3][3] == b[4][4])
    return true;
  // 检查副对角线
  if (b[0][4] != 0 && b[0][4] == b[1][3] && b[1][3] == b[2][2] &&
      b[2][2] == b[3][1] && b[3][1] == b[4][0])
    return true;
  return false;
}

// 按位置顺序填充棋盘（避免重复计数）
void dfs(int pos, int black_cnt, int white_cnt) {
  if (pos == 25) {
    // 棋盘填满：黑13个，白12个（黑先手）
    if (black_cnt == 13 && white_cnt == 12 && !hasWin()) {
      ans++;
    }
    return;
  }

  int x = pos / 5, y = pos % 5;

  // 尝试放黑子（黑先手，黑数 == 白数时放黑）
  if (black_cnt == white_cnt && black_cnt < 13) {
    b[x][y] = 2;
    dfs(pos + 1, black_cnt + 1, white_cnt);
    b[x][y] = 0;
  }
  // 尝试放白子（黑比白多1时放白）
  if (black_cnt == white_cnt + 1 && white_cnt < 12) {
    b[x][y] = 1;
    dfs(pos + 1, black_cnt, white_cnt + 1);
    b[x][y] = 0;
  }
}

int main() {
  dfs(0, 0, 0);
  cout << ans << endl;
  return 0;
}