#include <bits/stdc++.h>
using namespace std;

// tag: 树形DP，最大权独立集， 
// 2025.12.23

const int N = 6001;
vector<int> g[N], h(N), r(N); // 邻接表，节点权值，是否为根节点

// dp[p][0] 表示以 p 为根的子树中不选 p 的最大权值和
// dp[p][1] 表示以 p 为根的子树中且选 p 的最大权值和
int dp[N][2];

void dfs(int p) {
    dp[p][0] = 0;
    dp[p][1] = h[p];

    for (int k : g[p]) {
        dfs(k);
        dp[p][0] += max(dp[k][0], dp[k][1]);
        dp[p][1] += dp[k][0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        r[i] = true;
    }
    int l, k;
    for (int i = n + 2; i <= 2 * n; i++) {
        cin >> l >> k;
        g[k].push_back(l);
        r[l] = false;
    }
    // 找到根节点
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (r[i]) {
            root = i;
            break;
        }
    }

    dfs(root);

    cout << max(dp[root][0], dp[root][1]);
    return 0;
}