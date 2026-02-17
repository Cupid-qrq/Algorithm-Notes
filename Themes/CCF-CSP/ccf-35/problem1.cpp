#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    unordered_map<char, int> cnt;
    bool repeat = false;
    vector<bool> ch(3, false);
    for (char c : s) {
      cnt[c]++;
      if (cnt[c] > 2) {
        repeat = true;
      }
      if (isdigit(c)) {
        ch[0] = true;
      } else if (isalpha(c)) {
        ch[1] = true;
      } else if (c == '#' || c == '*') {
        ch[2] = true;
      }
    }
    if (ch[0] && ch[1] && ch[2]) {
      if (!repeat) {
        cout << 2 << endl;
        continue;
      }
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
  return 0;
}