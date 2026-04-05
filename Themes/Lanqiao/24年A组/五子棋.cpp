#include <bits/stdc++.h>
using namespace std;

int b[5][5]; // 1=白, 2=黑
long long ans = 0;

// 在按行优先顺序填到pos后，检查刚完成的行/列/对角线是否五连
bool checkWinAfter(int pos) {
  int x = pos / 5, y = pos % 5;

  // 当一行填完（y==4）时检查该行
  if (y == 4) {
    if (b[x][0] == b[x][1] && b[x][1] == b[x][2] && b[x][2] == b[x][3] &&
        b[x][3] == b[x][4])
      return true;
  }

  // 当一列填完（x==4）时检查该列
  if (x == 4) {
    if (b[0][y] == b[1][y] && b[1][y] == b[2][y] && b[2][y] == b[3][y] &&
        b[3][y] == b[4][y])
      return true;
  }

  // 主对角线在(4,4)填完时检查
  if (x == 4 && y == 4) {
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[2][2] == b[3][3] &&
        b[3][3] == b[4][4])
      return true;
  }

  // 副对角线在(4,0)填完时检查
  if (x == 4 && y == 0) {
    if (b[0][4] == b[1][3] && b[1][3] == b[2][2] && b[2][2] == b[3][1] &&
        b[3][1] == b[4][0])
      return true;
  }

  return false;
}

// 逐格放棋子，枚举所有C(25,13)种摆法，剪枝掉有五连的
void dfs(int pos, int wcnt, int bcnt) {
  if (pos == 25) {
    ans++;
    return;
  }

  int x = pos / 5, y = pos % 5;

  // 尝试放白子
  if (wcnt < 13) {
    b[x][y] = 1;
    if (!checkWinAfter(pos))
      dfs(pos + 1, wcnt + 1, bcnt);
    b[x][y] = 0;
  }

  // 尝试放黑子
  if (bcnt < 12) {
    b[x][y] = 2;
    if (!checkWinAfter(pos))
      dfs(pos + 1, wcnt, bcnt + 1);
    b[x][y] = 0;
  }
}

int main() {
  dfs(0, 0, 0);
  cout << ans << endl;
  return 0;
}