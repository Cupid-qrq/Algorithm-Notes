#include <bits/stdc++.h>
using namespace std;

// 2025.12.17
// tag: 带权并查集（银河英雄传说）

struct weightDSU {
    int n;
    // parent[i]：i的父节点
    // weight[i]：i到父节点的距离
    // sz[i]：以 i为根的集合大小
    vector<int> parent, weight, sz;

    weightDSU(int n) : n(n), parent(n + 1), sz(n + 1), weight(n + 1) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;  
            sz[i] = 1;      
            weight[i] = 0;  // 到根的距离为 0
        }
    }

    // 查找x的根节点，同时进行路径压缩，并维护x到根的距离
    int find(int x) {
        if (parent[x] == x) return x;
        int p = parent[x];
        parent[x] = find(p);
        // 在路径压缩时，累加到父节点的距离
        weight[x] += weight[p];
        return parent[x];
    }

    // 将x所在的整条链，接到y所在链的后面
    void unite(int x, int y) {
        int rootx = find(x); // 找到x的根，同时也维护了weight[x]
        int rooty = find(y);
        if (rootx == rooty) return;

        // rootx接到rooty后面
        parent[rootx] = rooty;

        // rootx到rooty的距离，等于rooty这条链当前的长度
        weight[rootx] = sz[rooty];

        // 更新集合大小
        sz[rooty] += sz[rootx];
    }

    // 查询x和y之间隔着多少个元素
    long long query(int x, int y) {
        if (find(x) != find(y)) return -1;
        // 两点到根的距离之差再-1
        return abs(weight[x] - weight[y]) - 1;
    }
};

int main() {
    int n = 30000;
    int t;
    cin >> t;
    weightDSU dsu(n);
    char c;
    int i, j;
    while (t--) {
        cin >> c >> i >> j;
        if (c == 'M') {
            dsu.unite(i, j);
        } else {
            cout << dsu.query(i, j) << endl;
        }
    }
    return 0;
}
