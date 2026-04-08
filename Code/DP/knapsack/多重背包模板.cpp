// 多重背包模板，洛谷P1776

// 最朴素的做法，就是拆解成01背包来做，比如物品i可以取s次，则拆成有s个物品i，进行01背包
// 注意01背包的先遍历物品再 倒序 遍历容量
// 时间复杂度 O(物品数*容量数*可取数)

// #include <bits/stdc++.h>
// using namespace std;

// const int N = 4e4 + 7;
// int n, w; // n件物品 ，总容量为w
// int dp[N], value[N], cost[N], cnt[N];

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);
//   cin >> n >> w;

//   for (int i = 1; i <= n; i++) {
//     cin >> value[i] >> cost[i] >> cnt[i];
//   }

//   for (int i = 1; i <= n; i++) {
//     for (int k = 1; k <= cnt[i]; k++) {
//       for (int j = w; j >= cost[i]; j--)
//         dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
//     }
//   }

//   cout << dp[w];

//   return 0;
// }

// 方法2，二进制优化：
// 对于物品i可以取s次，我们可以把s通过二进制拆分为几个分组，也就是二的幂次加上最后的余数
// 比如，s=17，可以拆成 1, 2, 4, 8,
// 2（最后的余数）这5组，每组都当成一个物品来处理，进行01背包
// 因为从0到s的所有取值都可以由这些二进制分组的物品组合而成，所以不会漏掉任何情况
// 时间复杂度 O(物品数*log(可取数)*容量数)

#include <bits/stdc++.h>
using namespace std;

const int N = 4e4 + 7;
int n, w; // n件物品 ，总容量为w
int dp[N], value[N], cost[N], cnt[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> w;

  for (int i = 1; i <= n; i++) {
    cin >> value[i] >> cost[i] >> cnt[i];
  }

  for (int i = 1; i <= n; i++) {
    int c = cnt[i], k = 1;
    while (k <= c) { // 每次取二的幂次，直到超过剩余的数量
      int curcost = k * cost[i], curvalue = k * value[i]; // 当前分组的总成本和总价值
      for (int j = w; j >= curcost; j--)  // 01背包的倒序遍历容量
        dp[j] = max(dp[j], dp[j - curcost] + curvalue);
      c -= k;
      k <<= 1; 
    }
    if(c){ // 处理最后余数的部分    
      int curcost = c * cost[i], curvalue = c * value[i];
      for (int j = w; j >= curcost; j--)
        dp[j] = max(dp[j], dp[j - curcost] + curvalue);
    }

  }

  cout << dp[w];

  return 0;
}


// 方法3，单调队列优化：
// 通过变形和数学转化，把dp等价为在定长窗口中取最值，采用单调队列
// 时间复杂度 O(物品数*容量数)
// 比较复杂，边界条件多