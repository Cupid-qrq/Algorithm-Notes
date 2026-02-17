// #include <bits/stdc++.h>

// using namespace std;

// int main() {
//     int m, s, t;
//     cin >> m >> s >> t;

//     vector<vector<int>> dp(t + 1, vector<int>(5 * t, -1));
//     for (int i = 1; i <= t; i++) {
//         for (int j = 0; j <= 3000; j++) {
//             if(dp[i-1][j]!=-1)
//                 dp[i][j] = max(dp[i][j], dp[i - 1][j] + 17);
//             if (j >= 4)
//                 dp[i][j] = max(dp[i][j], dp[i - 1][j - 4]);

//             dp[i][j] = max(dp[i][j], dp[i - 1][j + 10] + 60);
//             if (dp[i][j] >= s) {
//                 cout << "Yes" << endl << t;
//                 return 0;
//             }
//         }
//     }
//     int maxlen = -1;
//     for (int x : dp[t]) {
//         maxlen = max(maxlen, x);
//     }
//     cout << "No" << endl << maxlen << endl;

//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

// int main() {
//     int m, s, t;
//     cin >> m >> s >> t;

    // 魔法值上限：m + 4*t，但 t<=1000 时最多 4000+1000=5000
    // int MAX_MAGIC = m + 4 * t + 10;
    // vector<vector<int>> dp(t + 1, vector<int>(MAX_MAGIC, -1));

    // // 初始状态：0秒时，魔法=m，距离=0
    // dp[0][m] = 0;

    // for (int i = 1; i <= t; i++) {
    //     for (int j = 0; j < MAX_MAGIC; j++) {
    //         int best = -1;

    //         // 1. 跑步：魔法不变
    //         if (dp[i - 1][j] != -1) {
    //             best = max(best, dp[i - 1][j] + 17);
    //         }

    //         // 2. 闪烁：消耗10魔法，所以上一秒魔法是 j+10
    //         if (j + 10 < MAX_MAGIC && dp[i - 1][j + 10] != -1) {
    //             best = max(best, dp[i - 1][j + 10] + 60);
    //         }

    //         // 3. 休息：恢复4魔法，所以上一秒魔法是 j-4
    //         if (j >= 4 && dp[i - 1][j - 4] != -1) {
    //             best = max(best, dp[i - 1][j - 4]);
    //         }

    //         dp[i][j] = best;

    //         // 提前判断是否到达
    //         if (dp[i][j] >= s) {
    //             cout << "Yes" << endl << i << endl;
    //             return 0;
    //         }
    //     }
    // }

    // // 找 t 秒时的最大距离
    // int maxlen = 0;
    // for (int j = 0; j < MAX_MAGIC; j++) {
    //     if (dp[t][j] != -1) {
    //         maxlen = max(maxlen, dp[t][j]);
    //     }
    // }

//     int magic_dist = 0, dist = 0;
//     for (int i = 0; i < t;i++){
//         if(m>=10){
//             magic_dist += 60;
//             m -= 10;
//             dist += 17;
//         }
//         else{
//             if(dist<magic_dist){
//                 dist = magic_dist;
//                 dist += 17;
//                 m += 4;
//             }
//         }

//     } cout << "No" << endl << maxlen << endl;
//     return 0;
// }

int m, s, t, fla, run;  // 分别代表闪现距离，跑步距离
int main() {
    cin >> m >> s >> t;             // 读入;
    for (int i = 1; i <= t; i++) {  // 时间;

        if (m >= 10)
            m -= 10, fla += 60, run += 17;  // 蓝够了就闪,另一边跑步;
        else {
            if (fla > run) run = fla;  // 在最优的基础上跑;
            m += 4, run += 17;
        }  // 回蓝,另一边跑步;

        if (max(fla, run) >= s) {
            cout << "Yes" << endl << i << endl;
            return 0;
        }  // 出去了
    }
    cout << "No" << endl << max(fla, run) << endl;  // 没出去
    return 0;
}