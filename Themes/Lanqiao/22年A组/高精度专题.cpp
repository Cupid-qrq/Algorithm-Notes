#include <bits/stdc++.h>
using namespace std;

struct HighPrecision {
  // 小端存储：d[0] 是个位
  vector<int> d;

  HighPrecision() { d.push_back(0); }

  HighPrecision(long long x) { fromLongLong(x); }

  explicit HighPrecision(const string &s) { fromString(s); }

  void trim() {
    while (d.size() > 1 && d.back() == 0)
      d.pop_back();
  }

  void fromLongLong(long long x) {
    d.clear();
    if (x == 0) {
      d.push_back(0);
      return;
    }
    while (x > 0) {
      d.push_back(x % 10);
      x /= 10;
    }
  }

  void fromString(string s) {
    d.clear();
    int pos = 0;
    while (pos < (int)s.size() && s[pos] == '0')
      pos++; // 跳过前导零
    if (pos == (int)s.size()) {
      d.push_back(0);
      return;
    }
    for (int i = (int)s.size() - 1; i >= pos; i--)
      d.push_back(s[i] - '0');
    trim();
  }

  // 高精度加法和乘法
  friend HighPrecision operator+(const HighPrecision &a,
                                 const HighPrecision &b) {
    HighPrecision c;
    c.d.clear();
    int carry = 0;
    int n = max((int)a.d.size(), (int)b.d.size());
    for (int i = 0; i < n || carry; i++) {
      int sum = carry;
      if (i < (int)a.d.size())
        sum += a.d[i];
      if (i < (int)b.d.size())
        sum += b.d[i];
      c.d.push_back(sum % 10);
      carry = sum / 10;
    }
    c.trim();
    return c;
  }

  friend HighPrecision operator*(const HighPrecision &a,
                                 const HighPrecision &b) {
    HighPrecision c;
    c.d.assign(a.d.size() + b.d.size(), 0);
    for (int i = 0; i < (int)a.d.size(); i++) { // 拆分为a的每一位与b相乘
      int carry = 0;
      for (int j = 0; j < (int)b.d.size() || carry; j++) {
        long long cur = c.d[i + j] +
                        1LL * a.d[i] * (j < (int)b.d.size() ? b.d[j] : 0) +
                        carry;
        c.d[i + j] = cur % 10;
        carry = cur / 10;
      }
    }
    c.trim();
    return c;
  }

  friend istream &operator>>(istream &in, HighPrecision &x) {
    string s;
    in >> s;
    x.fromString(s);
    return in;
  }

  friend ostream &operator<<(ostream &out, const HighPrecision &x) {
    for (int i = (int)x.d.size() - 1; i >= 0; i--)
      out << x.d[i];
    return out;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HighPrecision a, b;
  cin >> a >> b;
  cout << (a + b) << '\n';
  cout << (a * b) << '\n';

  return 0;
}