#include <bits/stdc++.h>
using namespace std;

const int N = 10;
int cnt = 0;
vector<vector<char>> board(N, vector<char>(N));
int n, need;
int row0[N], row1[N], col0[N], col1[N];
int visit[N][N];

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool checkrow(int t, int x) {
    string s1(board[t].begin(), board[t].begin() + n);
    string s2(board[x].begin(), board[x].begin() + n);
    return s1 == s2;
}

bool checkcol(int c1, int c2) {
    string s1 = "", s2 = "";
    for (int i = 0; i < n; i++) {
        s1 += board[i][c1];
        s2 += board[i][c2];
    }
    return s1 == s2;
}

bool inboard(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void dfs(int x, int y, char num) {
    cnt++;

    if (!inboard(x, y)) return;
    if (visit[x][y] != 0) return;
    if (need==0) {
        print();
        exit(0);
    }

    // rule1
    int s = num - '0';
    if (s == 0) {
        if (row0[x] + 1 > n / 2 || col0[y] + 1 > n / 2) return;
    } else {
        if (row1[x] + 1 > n / 2 || col1[y] + 1 > n / 2) return;
    }

    // rule2
    if (x >= 2 && num == board[x-1][y] && num == board[x-2][y]) return;
if (x <= n-3 && num == board[x+1][y] && num == board[x+2][y]) return;
if (y >= 2 && num == board[x][y-1] && num == board[x][y-2]) return;
if (y <= n-3 && num == board[x][y+1] && num == board[x][y+2]) return;

    // modify the board
    board[x][y] = num;
    if (s == 0) {
        row0[x]++;
        col0[y]++;
    } else {
        row1[x]++;
        col1[y]++;
    }
    need--;
    visit[x][y] = 1;

    // rule3
    bool flag = true;
    if (row0[x] + row1[x] == n) {
        for (int t = 0; t < n; t++) {
            if (x != t && row0[t] + row1[t] == n && checkrow(t, x)) {
                flag = false;
                break;
            }
        }
    }
    if (col0[y] + col1[y] == n) {
        for (int t = 0; t < n; t++) {
            if (y != t && col0[t] + col1[t] == n && checkcol(t, y)) {
                flag = false;
                break;
            }
        }
    }

    // dfs process
    if (flag) {
        dfs(x + 1, y, '0');
        dfs(x + 1, y, '1');
        dfs(x - 1, y, '0');
        dfs(x - 1, y, '1');
        dfs(x, y + 1, '0');
        dfs(x, y + 1, '1');
        dfs(x, y - 1, '0');
        dfs(x, y - 1, '1');
    }

    // retrive the board
    board[x][y] = '_';
    if (s == 0) {
        row0[x]--;
        col0[y]--;
    } else {
        row1[x]--;
        col1[y]--;
    }
    need++;
    visit[x][y] = 0;
    return;
}

int main() {
    char c;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c;
            if (c == '1') {
                row1[i]++;
                col1[j]++;
                visit[i][j] = -1;
            } else if (c == '0') {
                row0[i]++;
                col0[j]++;
                visit[i][j] = -1;  //-1 is intrinsic num, shouldn't be modify ,0 is no visit
            } else {
                need++;
                visit[i][j] = 0;
            }
            board[i][j] = c;
        }
    }

    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            if (board[i][j] == '_') {
                dfs(i, j, '0');
                dfs(i, j, '1');
                return 0;
            }
        }
    }
    print();
    return 0;
}

