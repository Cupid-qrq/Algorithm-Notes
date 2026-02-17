#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vector<int> r1(n), r2(n), r3(n);
    for (int i = 0; i < n; i++) {
        cin >> r1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r2[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r3[i];
    }
    cin >> m;
    int sum = 0;
    int x1, x2, x3;
    x1 = x2 = x3 = 0;
    while (m--) {
        int n1, n2, n3;
        cin >> n1 >> n2 >> n3;
        x1 = (x1 + n1) % n;
        x2 = (x2 + n2) % n;
        x3 = (x3 + n3) % n;

        vector<int> t = {r1[x1], r2[x2], r3[x3]};
        sort(t.begin(), t.end());
        if (r1[x1] == r2[x2] && r2[x2] == r3[x3]) {
            sum += 200;
        } else if (r1[x1] == r2[x2] || r1[x1] == r3[x3] || r2[x2] == r3[x3]) {
            sum += 100;
        } else if (r3[x3] == r2[x2] + 1 && r2[x2] == r1[x1] + 1) {
            sum += 200;
        } else if (t[0] + 1 == t[1] && t[1] + 1 == t[2]) {
            sum += 100;
        }
    }
    cout << sum;
    return 0;
}