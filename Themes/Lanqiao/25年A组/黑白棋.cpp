#include <iostream>
#include <vector>
using namespace std;

const int N = 6;

// fixedBoard[i][j] = 0 表示未知，1 表示黑，2 表示白。
int fixedBoard[N][N];
int board[N][N];

struct Row {
  int a[N];
};

vector<Row> validRows;
vector<Row> choices[N];

bool rowOk(const Row &row) {
  int black = 0;
  for (int i = 0; i < N; i++) {
    if (row.a[i] == 1)
      black++;
  }
  if (black != 3)
    return false;

  for (int i = 0; i + 2 < N; i++) {
    if (row.a[i] == row.a[i + 1] && row.a[i + 1] == row.a[i + 2])
      return false;
  }
  return true;
}

bool matchFixed(int r, const Row &row) {
  for (int c = 0; c < N; c++) {
    if (fixedBoard[r][c] != 0 && fixedBoard[r][c] != row.a[c])
      return false;
  }
  return true;
}

bool checkBoard() {
  // 行：题目要求每行黑白各 3 个，且不能出现连续三个同色。
  for (int r = 0; r < N; r++) {
    int black = 0;
    for (int c = 0; c < N; c++) {
      black += (board[r][c] == 1);
    }
    if (black != 3)
      return false;
    for (int c = 0; c + 2 < N; c++) {
      if (board[r][c] == board[r][c + 1] && board[r][c + 1] == board[r][c + 2])
        return false;
    }
  }

  // 列：同样要求黑白各 3 个，且不能出现连续三个同色。
  for (int c = 0; c < N; c++) {
    int black = 0;
    for (int r = 0; r < N; r++) {
      black += (board[r][c] == 1);
    }
    if (black != 3)
      return false;
    for (int r = 0; r + 2 < N; r++) {
      if (board[r][c] == board[r + 1][c] && board[r + 1][c] == board[r + 2][c])
        return false;
    }
  }

  // 任意两行、任意两列都不能完全一样。
  for (int r1 = 0; r1 < N; r1++) {
    for (int r2 = r1 + 1; r2 < N; r2++) {
      bool same = true;
      for (int c = 0; c < N; c++) {
        if (board[r1][c] != board[r2][c]) {
          same = false;
          break;
        }
      }
      if (same)
        return false;
    }
  }

  for (int c1 = 0; c1 < N; c1++) {
    for (int c2 = c1 + 1; c2 < N; c2++) {
      bool same = true;
      for (int r = 0; r < N; r++) {
        if (board[r][c1] != board[r][c2]) {
          same = false;
          break;
        }
      }
      if (same)
        return false;
    }
  }

  return true;
}

void dfs(int r) {
  if (r == N) {
    if (!checkBoard())
      return;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (board[i][j] == 2)
          cout << 0;
        else
          cout << board[i][j];
      }
    }
    exit(0);
  }

  for (const auto &row : choices[r]) {
    for (int c = 0; c < N; c++) {
      board[r][c] = row.a[c];
    }
    dfs(r + 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 题目给定的初始棋盘。
  fixedBoard[0][0] = 1;
  fixedBoard[0][1] = 2;
  fixedBoard[0][3] = 2;
  fixedBoard[1][3] = 2;
  fixedBoard[2][4] = 2;
  fixedBoard[2][5] = 2;
  fixedBoard[4][2] = 1;
  fixedBoard[4][5] = 1;
  fixedBoard[5][1] = 2;
  fixedBoard[5][4] = 1;

  // 先枚举所有 6 格的行状态，只保留合法行。
  for (int mask = 0; mask < (1 << N); mask++) {
    Row row{};
    for (int i = 0; i < N; i++) {
      row.a[i] = (mask & (1 << i)) ? 1 : 2;
    }
    if (rowOk(row))
      validRows.push_back(row);
  }

  // 每一行只保留和初始盘面匹配的候选。
  for (int r = 0; r < N; r++) {
    for (const auto &row : validRows) {
      if (matchFixed(r, row))
        choices[r].push_back(row);
    }
  }

  // 直接按行枚举，最后统一检查整盘是否合法。
  dfs(0);
  return 0;
}