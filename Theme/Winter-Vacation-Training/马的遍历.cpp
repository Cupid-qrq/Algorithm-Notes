#include <bits/stdc++.h>
using namespace std;

// tag: bfs O(nm)

const int inf = 1e9;
vector<vector<int>> vis(401, vector<int>(401, inf));
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int n, m, x, y;

bool inmat(int nx, int ny) {
    return nx >= 1 && nx <= n && ny >= 1 && ny <= m;
}

int main() {
    cin >> n >> m >> x >> y;

    queue<pair<int, int>> q;
    q.push({x, y});
    vis[x][y] = 0;

    while (!q.empty()) {
        auto [curx, cury] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int nx = curx + dx[i], ny = cury + dy[i];
            if (inmat(nx, ny) && vis[nx][ny] == inf) {
                vis[nx][ny] = vis[curx][cury] + 1;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vis[i][j] != inf)
                cout << vis[i][j] << " ";
            else
                cout << -1 << " ";
        }
        cout << endl;
    }
    return 0;
}
