#include <bits/stdc++.h>
using namespace std;

// tag: 分治，递归 O(n^2)
// 2025.12.23

int k, Sz;
int px, py;

void print(int x, int y, int c) {
    cout << x << " " << y << " " << c << endl;
}

void solve(int x, int y, int len, int px, int py) {
    if (len == 1) return;

    int h = len / 2;
    int cx = h + x - 1;
    int cy = h + y - 1;

    // 障碍在左上部分
    if (px < x + h && py < y + h) {
        print(cx + 1, cy + 1, 1);
        solve(x, y, h, px, py);
        solve(x, y + h, h, cx, cy + 1);
        solve(x + h, y, h, cx + 1, cy);
        solve(x + h, y + h, h, cx + 1, cy + 1);
    } else if (px < x + h && py >= y + h)  // 在右上
    {
        print(cx + 1, cy, 2);
        solve(x, y, h, cx, cy);
        solve(x, y + h, h, px, py);
        solve(x + h, y, h, cx + 1, cy);
        solve(x + h, y + h, h, cx + 1, cy + 1);
    } else if (px >= x + h && py < y + h)  // 在左下
    {
        print(cx, cy + 1, 3);
        solve(x, y, h, cx, cy);
        solve(x + h, y, h, px, py);
        solve(x, y + h, h, cx, cy + 1);
        solve(x + h, y + h, h, cx + 1, cy + 1);
    } else if (px >= x + h && py >= y + h)  // 在右下
    {
        print(cx, cy, 4);
        solve(x, y, h, cx, cy);
        solve(x, y + h, h, cx, cy + 1);
        solve(x + h, y, h, cx + 1, cy);
        solve(x + h, y + h, h, px, py);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int px, py;
    cin >> k >> px >> py;
    Sz = 1 << k;

    solve(1, 1, Sz, px, py);

    return 0;
}