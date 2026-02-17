#include <bits/stdc++.h>
using namespace std;

// 树状数组模板2，支持区间修改与单点查询
// 区别在于对于原数组的，改为维护原数组的差分数组

struct fenwick {
    int n;
    vector<long long> tree;

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

    // one point query O(logn)
    long long query(int x) {
        long long res = 0;
        while (x > 0) {
            res += tree[x];
            x -= lowbit(x);
        }
        return res;
    }

    // range modify O(logn)
    void range_modify(int l, int r, int d) {
        modify(l, d);
        if (r+1 <= n) modify(r+1, -d);
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
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    vector<int> f(n + 1);
    f[1] = num[1];
    for (int i = 2; i <= n; i++) {
        f[i] = num[i] - num[i - 1];
    }
    fenwick tree(n);
    tree.build(f);
    while (m--) {
        int a, x, y, z;
        cin >> a >> x;
        if (a == 1) {
            cin >> y >> z;
            tree.range_modify(x, y, z);
        } else {
            cout << tree.query(x) << endl;
        }
    }
    return 0;
}