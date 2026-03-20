// 2026.2.27
// tag: 状态空间搜索 A* 启发式搜索
// AC方法：A*算法 + 曼哈顿距离启发函数

#include <bits/stdc++.h>
using namespace std;

/* ==================== 状态定义 ====================
 *
 * 状态：4×4棋盘 + 当前步数 + 该谁走
 * 目标：任意颜色形成四子一线（横/竖/斜）
 */

struct State {
  string board; // 16个字符表示棋盘，按行优先存储
  int step;     // 当前步数
  int h;        // 启发值

  bool operator>(const State &o) const {
    return step + h > o.step + o.h; // f(n) = g(n) + h(n)
  }
};

// 方向数组：上下左右
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

/* ==================== 启发函数设计 ====================
 *
 * h(n) = 估计到达目标状态的最少步数
 *
 * 策略：计算每种颜色形成四子一线的最小代价
 * - 枚举所有可能的四子一线（10条线：4横+4竖+2斜）
 * - 对每条线，计算需要移动多少步才能填满
 * - 取所有线中的最小值
 */
int heuristic(const string &board) {
  // 10条可能的四子一线
  vector<vector<int>> lines = {// 4条横线
                               {0, 1, 2, 3},
                               {4, 5, 6, 7},
                               {8, 9, 10, 11},
                               {12, 13, 14, 15},
                               // 4条竖线
                               {0, 4, 8, 12},
                               {1, 5, 9, 13},
                               {2, 6, 10, 14},
                               {3, 7, 11, 15},
                               // 2条斜线
                               {0, 5, 10, 15},
                               {3, 6, 9, 12}};

  int minCost = INT_MAX;

  for (auto &line : lines) {
    // 统计这条线上黑白棋子数量
    int blackCnt = 0, whiteCnt = 0;
    for (int pos : line) {
      if (board[pos] == 'B')
        blackCnt++;
      else if (board[pos] == 'W')
        whiteCnt++;
    }

    // 如果某种颜色已经占据了4个位置，距离目标0步
    if (blackCnt == 4 || whiteCnt == 4) {
      return 0;
    }

    // 如果这条线既有黑又有白，不可能形成四子一线
    if (blackCnt > 0 && whiteCnt > 0)
      continue;

    // 只有一种颜色，计算需要填充的空格数
    int needFill = 0;
    if (blackCnt > 0)
      needFill = 4 - blackCnt;
    else if (whiteCnt > 0)
      needFill = 4 - whiteCnt;
    else
      needFill = 3; // 全是空的，至少需要3步（4个棋子，第一个不用移动）

    minCost = min(minCost, needFill);
  }

  return minCost;
}

/* ==================== 检查是否达到目标状态 ====================
 *
 * 目标：任意颜色形成四子一线
 */
bool isGoal(const string &board) {
  vector<vector<int>> lines = {{0, 1, 2, 3},     {4, 5, 6, 7},   {8, 9, 10, 11},
                               {12, 13, 14, 15}, {0, 4, 8, 12},  {1, 5, 9, 13},
                               {2, 6, 10, 14},   {3, 7, 11, 15}, {0, 5, 10, 15},
                               {3, 6, 9, 12}};

  for (auto &line : lines) {
    char first = board[line[0]];
    if (first == 'O')
      continue;

    bool allSame = true;
    for (int i = 1; i < 4; i++) {
      if (board[line[i]] != first) {
        allSame = false;
        break;
      }
    }
    if (allSame)
      return true;
  }
  return false;
}

/* ==================== A* 搜索 ====================
 *
 * 优先队列：按 f(n) = g(n) + h(n) 排序
 * g(n) = step（已走步数）
 * h(n) = heuristic（启发值）
 */
int solve(string initial) {
  if (isGoal(initial))
    return 0;

  priority_queue<State, vector<State>, greater<State>> pq;
  unordered_set<string> visited;

  State start = {initial, 0, heuristic(initial)};
  pq.push(start);
  visited.insert(initial);

  while (!pq.empty()) {
    State cur = pq.top();
    pq.pop();

    // 找到所有空格位置（两个'O'）
    vector<int> emptyPos;
    for (int i = 0; i < 16; i++) {
      if (cur.board[i] == 'O') {
        emptyPos.push_back(i);
      }
    }

    // 对每个空格，尝试移动相邻的棋子
    for (int pos : emptyPos) {
      int x = pos / 4, y = pos % 4;

      // 尝试四个方向
      for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)
          continue;

        int npos = nx * 4 + ny;
        if (cur.board[npos] == 'O')
          continue; // 不能移动空格

        // 移动棋子到空格
        string newBoard = cur.board;
        swap(newBoard[pos], newBoard[npos]);

        if (visited.count(newBoard))
          continue;

        // 检查是否达到目标
        if (isGoal(newBoard)) {
          return cur.step + 1;
        }

        visited.insert(newBoard);
        State next = {newBoard, cur.step + 1, heuristic(newBoard)};
        pq.push(next);
      }
    }
  }

  return -1; // 无解
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string board = "";
  for (int i = 0; i < 4; i++) {
    string line;
    cin >> line;
    board += line;
  }

  cout << solve(board) << "\n";

  return 0;
}