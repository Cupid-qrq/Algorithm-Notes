#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  getline(cin, s);

  int n, m, k;
  cin >> n;
  cin.ignore();

  unordered_map<char, char> f;
  while (n--) {
    string tmp;
    getline(cin, tmp);
    f[tmp[1]] = tmp[2];
  }

  unordered_map<int, string> memo;
  cin >> m;

  while (m--) {
    string cur;
    cin >> k;
    k %= 63;
    auto iterator = memo.find(k);
    if (iterator != memo.end()) {
      cout << memo[k] << endl;
      continue;
    }
    int begin = 0;
    auto it = memo.find(k - 1);
    if (it != memo.end()) {
      cur = it->second;
      begin = k - 1;
    } else {
      cur = s;
    }

    for (int i = begin; i < k; i++) {
      for (char &c : cur) {
        if (c == '#')
          continue;
        if (f.find(c) != f.end())
          c = f[c];
      }
    }
    memo[k] = cur;
    cout << memo[k] << endl;
  }

  return 0;
}
