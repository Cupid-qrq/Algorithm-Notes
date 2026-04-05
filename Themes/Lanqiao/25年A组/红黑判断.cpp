#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    while (m--) {
        int n, k;
        cin >> n >> k;
        long long num = pow(2, n - 1) - 1 + k;
        int change = 0;
        while (num > 1) {
            change += num % 2;
            num /= 2;
        }
        if (change % 2) {
            cout << "BLACK" << endl;
        } else {
            cout << "RED" << endl;
        }
    }
    return 0;
}