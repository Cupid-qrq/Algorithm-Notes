#include <bits/stdc++.h>
using namespace std;

// tag: 区间DP 

int main() {
    string s;
    getline(cin, s);
    int n = s.size();

    // dp[i][j]: 涂好 s[i..j] 所需最少次数
    vector<vector<int>> dp(n, vector<int>(n, 1e9));

    // 初始化单个字符的情况
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    // 枚举区间长度 len 从 2 到 n
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            if (s[i] == s[j]) { // 端点字符相同
                dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]);
            } else { // 端点字符不同
                for(int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}

/*
时间复杂度分析：
对于每个区间长度 len，从 2 到 n，共有 n-1 种长度；
对于每个长度 len，有 n-len+1 个起点 i；
对于每个区间 s[i..j]，需要枚举所有可能的分割点 k，共有 j-i 个选择；
因此，总时间复杂度为 O(n^3)。

空间复杂度分析：
使用了一个二维数组 dp，大小为 n x n，因此空间复杂度为 O(n^2)。
*/