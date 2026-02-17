#include <bits/stdc++.h>
using namespace std;

// tag: BFS O(nm)

const int N = 305;
char grid[N][N];
int dist[N][N];
int n, m, sx, sy, ex, ey;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
vector<pair<int, int>> gate[26];  // 存储每个字母对应的两个端点

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '@') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == '=') {
                ex = i;
                ey = j;
            } else if (grid[i][j] >= 'A' && grid[i][j] <= 'Z') {
                gate[grid[i][j] - 'A'].push_back({i, j});
            }
        }
    }

    memset(dist, -1, sizeof(dist));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == ex && y == ey) {
            cout << dist[x][y] << '\n';
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#') continue;

            // 移动到滑梯端点时，立即传送到另一个端点
            if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'Z') {
                int idx = grid[nx][ny] - 'A';
                int px = -1, py = -1;

                for (auto& p : gate[idx]) {
                    if (p.first == nx && p.second == ny) continue;
                    px = p.first;
                    py = p.second;
                }
                if (px != -1 && py != -1 && dist[px][py] == -1) {
                    dist[px][py] = dist[x][y]+1;
                    q.push({px, py});
                }
            }

            else if (dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return 0;
}