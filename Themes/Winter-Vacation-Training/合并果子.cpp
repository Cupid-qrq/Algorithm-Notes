#include <bits/stdc++.h>
using namespace std;

// tag: 哈夫曼编码，O(nlogn)

typedef unsigned long long ULL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // 优先队列（小根堆），每次取出两个最小的数合并
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        q.push(a);
    }

    ULL total = 0;
    while (q.size() > 1) {
        ULL a = q.top();
        q.pop();
        ULL b = q.top();
        q.pop();
        ULL tmp = a + b;
        total += (tmp);
        q.push(tmp);
    }

    cout << total;
    return 0;
}