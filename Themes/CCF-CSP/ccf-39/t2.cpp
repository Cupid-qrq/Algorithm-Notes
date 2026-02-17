#include <bits/stdc++.h>
using namespace std;

bool match(const vector<vector<int>>& tmp, const int* csp, int i, int j) {
    for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 9; ++y)
            if (tmp[i + x][j + y] != csp[x * 9 + y]) return false;
    return true;
}

int main() {
    int n, l;
    cin >> n >> l;
    int csp[45] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1,
                   1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    vector<vector<int>> graph(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> graph[i][j];

    for (int k = 1; k < l; k++) {
        vector<vector<int>> tmp(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) tmp[i][j] = (graph[i][j] >= k);

        bool found = false;
        for (int i = 1; i <= n - 4 && !found; i++)
            for (int j = 1; j <= n - 8 && !found; j++)
                if (match(tmp, csp, i, j)) {
                    cout << k << endl;
                    found = true;
                }
    }
    return 0;
}