#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 7;

vector<int> adj[N];
int n;

int fa[N];
char ch[N];
long long f[N];
long long sumv[N];
bool pushedOpen[N];
int matchedOpen[N];
long long ans;
vector<int> openStack;

void dfs(int u) {
  pushedOpen[u] = false;
  matchedOpen[u] = 0;

  if (ch[u] == '(') {
    openStack.push_back(u);
    pushedOpen[u] = true;
  } else if (!openStack.empty()) {
    int leftNode = openStack.back();
    openStack.pop_back();
    matchedOpen[u] = leftNode;
    f[u] = f[fa[leftNode]] + 1;
  }

  sumv[u] = sumv[fa[u]] + f[u];
  ans ^= 1LL * u * sumv[u];

  for (int v : adj[u]) {
    dfs(v);
  }

  if (pushedOpen[u]) {
    openStack.pop_back();
  } else if (matchedOpen[u] != 0) {
    openStack.push_back(matchedOpen[u]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  string s;
  cin >> s;
  for (int i = 1; i <= n; i++)
    ch[i] = s[i - 1];

  for (int i = 2; i <= n; i++) {
    cin >> fa[i];
    adj[fa[i]].push_back(i);
  }

  ans = 0;
  openStack.reserve(n);

  dfs(1);

  cout << ans << '\n';

  return 0;
}