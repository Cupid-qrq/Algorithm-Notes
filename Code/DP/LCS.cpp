#include <algorithm>  // 添加此行以支持std::reverse
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

string X = "1001010";
string Y = "0101101";
int m, n;
vector<vector<int>> dp;

// 递归查找所有LCS
void findAllLCS(int i, int j, string currentLCS, set<string>& allLCS) {
    // 如果到达边界，保存当前LCS
    if (i == 0 || j == 0) {
        allLCS.insert(currentLCS);
        return;
    }

    // 如果字符相等，加入当前LCS
    if (X[i - 1] == Y[j - 1]) {
        findAllLCS(i - 1, j - 1, X[i - 1] + currentLCS, allLCS);
    } else {
        // 如果上方的值等于当前值，向上回溯
        if (dp[i - 1][j] == dp[i][j]) {
            findAllLCS(i - 1, j, currentLCS, allLCS);
        }
        // 如果左边的值等于当前值，向左回溯
        if (dp[i][j - 1] == dp[i][j]) {
            findAllLCS(i, j - 1, currentLCS, allLCS);
        }
    }
}

int main() {
    m = X.length();
    n = Y.length();

    // 创建dp数组
    dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

    // 填充dp数组
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 存储所有LCS
    set<string> allLCS;
    findAllLCS(m, n, "", allLCS);

    // 输出dp表
    cout << "\n";
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"LCS len: "<<dp[m][n]<<endl;

    // 输出所有LCS
    cout << "each LCS: \n";
    for (const string& lcs : allLCS) {
        cout << lcs << endl;
    }

    return 0;
}