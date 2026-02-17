#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 10000000;

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int sigma[N + 1];

void init() {
    for (int i = 1; i <= N; ++i)
        for (int j = i; j <= N; j += i) sigma[j] = (sigma[j] + i) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int op, n;
    cin >> op >> n;

    long long ans = 0;

    // Enumerate y, z, k such that b = k*y*z <= n and gcd(y,z)=1
    // For op=0: sum y^3 * sigma(k^2 * z)
    // We enumerate y and z first
    for (int y = 1; y <= n; ++y) {
        if (1LL * y * y * y > 1e18) break;  // not needed
        for (int z = 1; 1LL * y * z <= n; ++z) {
            if (gcd(y, z) != 1) continue;
            int max_k = n / (y * z);
            if (max_k == 0) break;
            // Precompute sum_{k=1}^{max_k} sigma(k*k*z)
            // But k*k*z may > N, so only do when z is small
            if (z > 1000) {
                for (int k = 1; k <= max_k; ++k) {
                    long long arg = 1LL * k * k * z;
                    if (arg <= N) {
                        ans = (ans + 1LL * y * y % MOD * y % MOD * sigma[arg]) % MOD;
                    } else {
                        // compute sigma(arg) by trial division (rare)
                        long long s = 0;
                        for (long long d = 1; d * d <= arg; ++d) {
                            if (arg % d == 0) {
                                s += d;
                                if (d * d != arg) s += arg / d;
                            }
                        }
                        ans = (ans + 1LL * y * y % MOD * y % MOD * (s % MOD)) % MOD;
                    }
                }
            } else {
                for (int k = 1; k <= max_k; ++k) {
                    int arg = k * k * z;
                    if (arg <= N) {
                        ans = (ans + 1LL * y * y % MOD * y % MOD * sigma[arg]) % MOD;
                    } else
                        break;  // for small z, k large makes arg > N
                }
            }
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}