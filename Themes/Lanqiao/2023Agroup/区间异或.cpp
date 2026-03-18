#include <bits/stdc++.h>
using namespace std;

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   int n;
//   long long num;
//   cin >> n;
//   vector<long long> preXOR(n + 1, 0);
//   for (int i = 1; i <= n; i++) {
//     cin >> num;
//     preXOR[i] = preXOR[i - 1] ^ num;
//   }

//   long long ans = 0;
//   for (int l = 1; l <= n; l++) {
//     for (int r = l; r <= n; r++) {
//       ans += preXOR[l - 1] ^ preXOR[r];
//     }
//   }
//   cout << ans;
//   return 0;
// }

/* AC算法：区间异或和可以用按位来算贡献，枚举每一位1的情况，统计前缀异或和中该位为1的个数，贡献为 count * (n - count) * 2^bit

例如[1,2]，对应二进制为01，10
考虑每个的第一位，得到前缀异或和为[0,1,1],有2个1，1个0，贡献为 2 * 1 * 2^0 = 2
考虑每个的第二位，得到前缀异或和为[0,0,1],有1个1，2个0，贡献为 1 * 2 * 2^1 = 4
总贡献为2 + 4 = 6

形式化的算法如下：
对每一位单独算异或前缀和，统计该位为1的个数 count，贡献为 count * (n - count) * 2^bit
最终答案为所有位贡献之和
*/
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  long long num;
  cin >> n;
  vector<long long> preXOR(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> num;
    preXOR[i] = preXOR[i - 1] ^ num;
  }

  long long ans = 0;
  for (int bit = 0; bit < 60; bit++) {
    long long count = 0;
    for (int i = 0; i <= n; i++) {
      if (preXOR[i] & (1LL << bit))
        count++;
    }
    ans += count * (n + 1 - count) * (1LL << bit);
  }
  cout << ans;
  return 0;
}