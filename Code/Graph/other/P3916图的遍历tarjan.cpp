#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> g[N], scc[N], dag[N];
int n, m;

int dfn[N], low[N], sccId[N], sccCnt, idx;
bool inStack[N];
int dp[N], vis[N];
stack<int> st;

void tarjan(int u) {
  dfn[u] = low[u] = ++idx;
  st.push(u);
  inStack[u] = true;

  for (int v : g[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (inStack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }

  if (dfn[u] == low[u]) {
    sccCnt++;
    int x;
    do {
      x = st.top();
      st.pop();
      inStack[x] = false;
      sccId[x] = sccCnt;
      scc[sccCnt].push_back(x);
    } while (x != u);
  }
}

// Memoized DP: compute max node reachable from SCC id
int computeDP(int id) {
  if (vis[id])
    return dp[id];
  vis[id] = 1;

  // Initialize with max node in this SCC
  for (int node : scc[id]) {
    dp[id] = max(dp[id], node);
  }

  // Extend through outgoing edges in DAG
  for (int next : dag[id]) {
    dp[id] = max(dp[id], computeDP(next));
  }

  return dp[id];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }

  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i);

  // Build DAG between SCCs (avoid duplicate edges with set)
  set<pair<int, int>> dagEdges;
  for (int u = 1; u <= n; u++) {
    for (int v : g[u]) {
      int idU = sccId[u];
      int idV = sccId[v];
      if (idU != idV && !dagEdges.count({idU, idV})) {
        dagEdges.insert({idU, idV});
        dag[idU].push_back(idV);
      }
    }
  }

  // Compute DP for each SCC
  for (int i = 1; i <= sccCnt; i++) {
    computeDP(i);
  }

  // Output: for each original node, answer is dp of its SCC
  for (int i = 1; i <= n; i++)
    cout << dp[sccId[i]] << " ";
    
  return 0;
}