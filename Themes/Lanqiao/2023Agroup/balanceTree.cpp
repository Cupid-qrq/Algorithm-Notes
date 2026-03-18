// 80分，AC算法为树上启发式合并或者线段树，莫队算法

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> c;
vector<vector<int>> child;

// 收集以 u 为根的整棵子树颜色频次
void collect(int u, unordered_map<int, int> &freq) {
  freq[c[u]]++;
  for (int v : child[u])
    collect(v, freq);
}

// 判断以 root 为根的子树是否颜色平衡
bool isBalanced(int root) {
  unordered_map<int, int> freq;
  collect(root, freq);

  int target = -1;
  for (auto &kv : freq) {
    if (target == -1)
      target = kv.second;
    else if (kv.second != target)
      return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  c.resize(n + 1);
  child.assign(n + 1, {});

  for (int i = 1; i <= n; i++) {
    int p;
    cin >> c[i] >> p;
    if (p)
      child[p].push_back(i);
  }

  long long ans = 0;
  for (int u = 1; u <= n; u++) {
    if (isBalanced(u))
      ans++;
  }

  cout << ans << '\n';
  return 0;
}