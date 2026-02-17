#include <bits/stdc++.h>
using namespace std;

// 2025.12.3
// tag: 贪心

int main() {
    int x, n;
    cin >> x >> n;
    if (x < 1) return 0;
    vector<int> current(n);
    for (int i = 0; i < n; i++) cin >> current[i];
    sort(current.begin(), current.end());

    // 贪心选择每次能覆盖的最大面值硬币
    if (current[0] != 1) return -1;
    int curmax = 0, ans = 0;
    while (curmax < x) {
        int coin;
        // 如果当前硬币面值小于等于curmax+1，则选择该硬币
        for (int i = 0; i < n; i++) {
            if (current[i] <= curmax + 1) {
                coin = current[i];
            } else
                break;
        }
        // 选择该硬币后，更新curmax
        curmax += coin;
        // cout << "choose :" << coin << endl;
        // cout << "now curmax is: " << curmax << endl;
        ans++;
    }

    cout << ans;
    return 0;
}