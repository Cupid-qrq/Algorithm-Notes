// 常规做法，80分
/*
#include <bits/stdc++.h>
using namespace std;
vector<int> nums;
long long ans;

bool check(int l, int r) {
  if (l == r || r == l + 1)
    return true;

  int cnt = 1, cur = nums[l];
  for (int i = l + 1; i <= r; i++) {
    if (nums[i] - cur >= 2 || nums[i] < cur)
      cnt++;
    cur = nums[i];
    if (cnt > 2)
      return false;
  }
  return true;
}

int main() {
  string s;
  cin >> s;
  int n = s.size();
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    nums[i] = s[i] - '0';
  }

  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (check(l, r)) {
        ans++;
        //cout << "ok(l,r): " << l << " " << r << endl;
      }
    }
  }
  cout << ans;
  return 0;
}

*/

// AC solution： sliding window

#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  int n = s.size();
  vector<int> nums;
  for (char &c : s) {
    nums.push_back(c - '0');
  }

  long long ans = 0;
  int l = 0, bad = 0;
  for (int r = 0; r < n; r++) {
    // 更新当前区间内坏边数量
    if (r > 0) {
      if (nums[r] < nums[r - 1] || nums[r] - nums[r - 1] >= 2)
        bad++;
    }

    // 不断移动窗口左端，直到区间内坏边数<=1，此时区间内以r为结尾的子区间都是合法的，更新答案
    while(bad>1){
      l++;
      if (nums[l] < nums[l - 1] || nums[l] - nums[l - 1] >= 2)
        bad--;
    }

    ans += r - l + 1;
  }
  cout << ans;
  return 0;
}