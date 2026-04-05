#include <bits/stdc++.h>
using namespace std;

using i64 = long long;   // 64位整数，用于存储求和结果
using i128 = __int128_t; // 128位整数，防止方差计算溢出

/**
 * 检查前 x 个成绩中是否能选出 k 个成绩，其方差小于 T
 * 核心思想：排序后，最小方差子集必为连续窗口
 * 使用方差公式的整数形式避免浮点误差
 * σ² < T  ⟺  k*Σv_i² - (Σv_i)² < T*k²
 */
static bool canPickWithSmallVariance(const vector<int> &a, int x, int k,
                                     i64 T) {
  // 取前 x 个成绩并排序（排序后最小方差在连续窗口中取得）
  vector<int> b(a.begin(), a.begin() + x);
  sort(b.begin(), b.end());

  // 预计算前缀和与前缀平方和，用于 O(1) 快速计算窗口内的和与平方和
  vector<i64> prefixSum(x + 1, 0), prefixSq(x + 1, 0);
  for (int i = 0; i < x; ++i) {
    prefixSum[i + 1] = prefixSum[i] + b[i];
    prefixSq[i + 1] = prefixSq[i] + 1LL * b[i] * b[i];
  }

  // 阈值：T * k²（用于整数比较）
  i128 right = (i128)T * k * k;

  // 枚举长度为 k 的连续窗口
  for (int r = k; r <= x; ++r) {
    int l = r - k;
    i64 sum = prefixSum[r] - prefixSum[l]; // 窗口内元素和
    i64 sq = prefixSq[r] - prefixSq[l];    // 窗口内元素平方和

    // 计算方差的分子部分：k*Σv_i² - (Σv_i)²
    i128 left = (i128)k * sq - (i128)sum * sum;
    // 如果 left < right，则方差 < T
    if (left < right) {
      return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 输入：n 个学生成绩，每次要选 k 个，目标方差阈值 T
  int n, k;
  i64 T;
  cin >> n >> k >> T;

  // 读取所有成绩
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  // ========== 二分查找最小需要检查的人数 ==========
  // 不变量：left = 第一个可行的前缀长度，right = 最后检查的长度
  int left = k, right = n; // 至少需要 k 个人（无法选 k 个否则）
  int ans = -1;            // 若无解则输出 -1

  while (left <= right) {
    int mid = left + (right - left) / 2; // 中间检查点

    if (canPickWithSmallVariance(a, mid, k, T)) {
      // mid 个人足以找到符合条件的 k 个成绩
      ans = mid;
      right = mid - 1; // 继续寻找更少的人数
    } else {
      // mid 个人无法找到符合条件的 k 个成绩
      left = mid + 1; // 需要更多人
    }
  }

  // 输出答案：最少需要检查的人数，无解则输出 -1
  cout << ans;
  return 0;
}