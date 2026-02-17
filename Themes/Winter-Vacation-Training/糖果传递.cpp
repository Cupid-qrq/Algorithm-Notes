#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// tag: 糖果传递问题，贪心，前缀和，中位数 O(nlogn)
// 2025.12.23

// 数学证明：
/*
    定义不平衡量b[i] = a[i] - avg，表示第 i 个孩子手中多余或缺少的糖果数
    显然 sum(b[i]) = 0
    定义f为(i,i+1)之间传递的糖果数,类似于网络流中的流量
    则对于每个孩子 i，有：
        f[i-1] - f[i] = b[i]
    推导可得：
        f[1] = f[0] - b[1]
    以此类推可得：
        f[i] = f[0] - (b[1] + b[2] + ... + b[i])
    定义前缀不平衡量
        c[i] = b[1] + b[2] + ... + b[i]
    则  f[i] = f[0] - c[i]
    故cost = sum(|f[i]|) = sum(|f[0] - c[i]|)
    由于 f[0] 是一个变量，我们需要选择一个合适的值使得 cost 最小化
    观察可知，cost 关于 f[0] 是一个分段线性函数，其拐点出现在 c[i] 处
    因此，最优的 cost(f[0]) 一定出现在某个 c[i] 处
    进一步分析可知，cost(f[0]) 关于 f[0] 的导数在 f[0] < median(c) 时为负，在 f[0] > median(c) 时为正
    因此，cost 在 f[0] = median(c) 处取得最小值
    故我们只需计算 cost(median(c)) 即可
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll sum = 0;
    for (ll x : a) sum += x;
    ll avg = sum / n;

    // 前缀不平衡量
    vector<ll> c(n);
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i] - avg;
        c[i] = cur;
    }

    sort(c.begin(), c.end());
    ll median = c[n / 2];

    ll ans = 0;
    for (ll x : c) {
        ans += llabs(x - median);
    }

    cout << ans;
    return 0;
}
