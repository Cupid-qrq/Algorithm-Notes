#include <bits/stdc++.h>
using namespace std;

// 树状数组模板1，支持单点修改与区间查询 


struct fenwick {
    int n;
    vector<int> tree;

    fenwick(int n) : n(n), tree(n + 1, 0) {
    }

    int lowbit(int x) {
        return x & -x;
    }

    // build tree O(n)
    void build(const vector<int>& num) {
        for (int i = 1; i <= n; i++) {
            tree[i] += num[i];
            int j = i + lowbit(i);
            if (j <= n) tree[j] += tree[i];
        }
    }

    // prefix sum O(logn)
    long long presum(int x) {
        long long res = 0;
        while (x > 0) {
            res += tree[x];
            x -= lowbit(x);
        }
        return res;
    }

    // range sum O(logn)
    long long range_sum(int l, int r) {
        return presum(r) - presum(l-1);
    }

    // modify O(logn)
    void modify(int pos, int d) {
        while (pos <= n) {
            tree[pos] += d;
            pos += lowbit(pos);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> num(n + 1);
    for (int i = 1; i <= n; i++) cin >> num[i];
    fenwick tree(n);
    tree.build(num);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            tree.modify(b, c);
        } else {
            cout << tree.range_sum(b, c) << endl;
        }
    }

    return 0;
}