#include <bits/stdc++.h>
using namespace std;

const int N = 405, MAXN = 1e6;
char g[N][N];
int z, k, op, t, cnt;
vector<int> para[MAXN];

void whirl(int u, int v, int l, int d) {
  int down = u + l - 1, right = v + l - 1;
  // 只实现顺时针
  for (int i = 0; i < d; i++) {
    char tmp[N][N] = {};
    for (int a = u; a <= down; a++) {
      for (int b = v; b <= right; b++) {
        int lgap = b - v, dgap = down - a;
        tmp[u + lgap][v + dgap] = g[a][b];
      }
    }
    for (int a = u; a <= down; a++) {
      for (int b = v; b <= right; b++) {
        g[a][b] = tmp[a][b];
      }
    }
  }
}

void change(int u, int d, int l, int r, int o) {
  int width = d - u + 1, length = r - l + 1;
  if (o == 1) {
    for (int a = 0; a < width / 2; a++) {
      for (int b = l; b <= r; b++) {
        swap(g[u + a][b], g[d - a][b]);
      }
    }
  } else {
    for (int a = 0; a < length / 2; a++) {
      for (int b = u; b <= d; b++) {
        swap(g[b][l + a], g[b][r - a]);
      }
    }
  }
}

void final(int n, int m) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << g[i][j];
    }
    cout << '\n';
  }
}

int main() {
  cin >> z;
  for (int i = 1; i <= z; i++)
    for (int j = 1; j <= z; j++)
      cin >> g[i][j];
  // cout << "ok1" << endl;
  cin >> k >> t;
  for (int i = 0; i < t; i++) {
    int u, v, l, d, r;
    cin >> op >> u >> v >> l >> d >> r;
    para[i] = {op, u, v, l, d, r};
  }

  for (int i = t - 1; i >= 0; i--) {
    int op = para[i][0];
    if (op == 1) {
      int u = para[i][1], v = para[i][2], l = para[i][3], d = para[i][4],
          r = para[i][5];
      whirl(1, 1, z, r % 4);
      whirl(u, v, l, (4 - d / 90) % 4);

    } else {
      int u = para[i][1], d = para[i][2], l = para[i][3], r = para[i][4],
          o = para[i][5];
      change(u, d, l, r, o);
    }
  }

  int n = -1, m = -1;
  for (int i = 1; i <= z; i++) {
    if (g[i][1] == '?') {
      n = i - 1;
      break;
    }
  }
  if (n == -1)
    n = z;
  for (int i = 1; i <= z + 1; i++) {
    if (g[1][i] == '?') {
      m = i - 1;
      break;
    }
  }
  if (m == -1)
    m = z;

  cout << n << " " << m << '\n';
  final(n, m);
  return 0;
}

/*
4
q?qr
????
l?xr
????
13 2
2 1 2 2 4 2
2 2 3 1 4 1

3
123
456
789
7 1
1 1 1 3 90 0

*/