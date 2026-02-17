#include <bits/stdc++.h>
using namespace std;

// 2025.12.17
// tag: dfs+记忆化搜索 O(n^2)

const int N = 101;
int dp[N][N];
int h[N][N];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int r, c;

int dfs(int x, int y) {
    if (dp[x][y] != 0) return dp[x][y];
    dp[x][y]++;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 1 || nx > r || ny < 1 || ny > c) continue;
        if (h[nx][ny] < h[x][y]) {
            dp[x][y] = max(dp[x][y], 1 + dfs(nx, ny));
        }
    }
    return dp[x][y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> h[i][j];
        }
    }

    // dp[i][j] = 从（i，j）出发的最长路
    int ans = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans;
    return 0;
}