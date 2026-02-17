#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;
    double x, y, cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        if ((x * x + y * y) <= a * a) cnt++;
    }
    
    cout << (4.0 * cnt) / (1.0*n);
    return 0;
}