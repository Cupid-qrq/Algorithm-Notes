/*
 * 算法思路：
 * - 定义 dp[i][j][k] 表示从区间 [i, j] 的路灯关闭完毕，
 *   且最后一个关闭的路灯是 k（0 表示左端点，1 表示右端点）时的最小代价。
 * - 状态转移方程基于从左到右或从右到左关闭路灯的代价计算。
 * - 使用前缀和数组快速计算区间内的权重和。
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;
int main() {
    int n, c;
    cin >> n >> c;
    vector<int> p(n + 1, 0), w(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> w[i];
    }
    vector<ll> prefix(n + 1, 0); // 前缀和预处理，prefix[i]表示前i个路灯的权重和
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + w[i];
    }

    // dp[i][j][k]: i到j区间内的路灯关闭完毕，最后一个关闭的是k(0表示左端点，1表示右端点)时的最小代价
    vector<vector<vector<ll>>> dp(n + 2, vector<vector<ll>>(n + 2, vector<ll>(2, inf)));
    dp[c][c][1] = dp[c][c][0] = 0;
    for (int i = c; i >= 1; i--) {
        for (int j = c; j <= n; j++) {
            if (i == j && i == c) continue; // 如果区间只有一个路灯且是初始位置，跳过
           
            if (i < j) {
                ll remain_left = prefix[n] - (prefix[j] - prefix[i]); // 计算剩余左侧路灯的权重和
                // 从左端点关闭路灯
                dp[i][j][0] = min(dp[i + 1][j][0] + remain_left * (p[i + 1] - p[i]),
                                  dp[i + 1][j][1] + remain_left * (p[j] - p[i]));

                ll remain_right = prefix[n] - (prefix[j - 1] - prefix[i - 1]);
                dp[i][j][1] = min(dp[i][j - 1][1] + remain_right * (p[j] - p[j - 1]),
                                  dp[i][j - 1][0] + remain_right * (p[j] - p[i]));

            }
        }
    }
    cout << min(dp[1][n][0], dp[1][n][1]);
    return 0;
}

