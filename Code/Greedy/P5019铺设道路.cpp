// 2026.2.25
// tag: 贪心，差分

/* 题意：有n个路口，每个路口有一个高度，初始时所有路口的高度为0。每次可以选择一个路口，将其高度增加1，同时将与其相邻的路口的高度也增加1。问最少需要多少次操作才能使得所有路口的高度都达到给定的高度。

考虑贪心性，当前路口的高度小于目标高度时，必须对其进行操作。每次操作会将当前路口和相邻路口的高度增加1，因此可以通过差分数组来记录每个路口需要增加的高度。最终答案就是所有正数差分的和。即当arr[i]
> arr[i-1]时，ans += arr[i] - arr[i-1]。

复杂度：O(n)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> dif(n + 2, 0), arr(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  for (int i = 1; i <= n; i++) {
    dif[i] = arr[i] - arr[i - 1];
  }
  int ans = arr[1];
  for (int i = 2; i <= n; i++) {
    if (arr[i] > arr[i - 1])
      ans += dif[i];
  }
  cout << ans;
  return 0;
}