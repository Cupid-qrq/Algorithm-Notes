#include <bits/stdc++.h>
using namespace std;

struct node {
  int left, right;
};
vector<node> tree;
int getDepth(int cur) {
  if (cur == 0)
    return 0;
  int l = tree[cur].left;
  int r = tree[cur].right;

  return 1 + max(getDepth(l), getDepth(r));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  tree.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> tree[i].left >> tree[i].right;
  }

  cout << getDepth(1);

  return 0;
}