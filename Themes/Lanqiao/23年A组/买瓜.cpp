#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll M;
vector<ll> a;

ll target;
int midPos;
int ans;

vector<pair<ll, int>> leftStates;
vector<ll> leftSums;
vector<int> leftMinCuts;
vector<ll> suf;

void dfsLeft(int idx, int end, ll sum, int cuts) {
  if (sum > target)
    return;
  if (idx == end) {
    leftStates.push_back({sum, cuts});
    return;
  }

  dfsLeft(idx + 1, end, sum, cuts);
  dfsLeft(idx + 1, end, sum + a[idx], cuts + 1);
  dfsLeft(idx + 1, end, sum + 2 * a[idx], cuts);
}

void buildLeftMap() {
  sort(leftStates.begin(), leftStates.end(),
       [](const pair<ll, int> &x, const pair<ll, int> &y) {
         if (x.first != y.first)
           return x.first < y.first;
         return x.second < y.second;
       });

  for (size_t i = 0; i < leftStates.size();) {
    size_t j = i;
    int best = leftStates[i].second;
    while (j < leftStates.size() &&
           leftStates[j].first == leftStates[i].first) {
      best = min(best, leftStates[j].second);
      ++j;
    }
    leftSums.push_back(leftStates[i].first);
    leftMinCuts.push_back(best);
    i = j;
  }
}

void dfsRight(int idx, ll sum, int cuts) {
  if (sum > target)
    return;
  if (cuts >= ans)
    return;
  if (sum + suf[idx] < target)
    return;

  if (idx == n) {
    ll need = target - sum;
    auto it = lower_bound(leftSums.begin(), leftSums.end(), need);
    if (it != leftSums.end() && *it == need) {
      int pos = (int)(it - leftSums.begin());
      ans = min(ans, cuts + leftMinCuts[pos]);
    }
    return;
  }

  dfsRight(idx + 1, sum + 2 * a[idx], cuts);
  dfsRight(idx + 1, sum, cuts);
  dfsRight(idx + 1, sum + a[idx], cuts + 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> M;
  target = 2 * M;

  a.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  sort(a.begin(), a.end(), greater<ll>());

  midPos = n / 2;

  dfsLeft(0, midPos, 0, 0);
  buildLeftMap();

  suf.assign(n + 1, 0);
  for (int i = n - 1; i >= midPos; --i)
    suf[i] = suf[i + 1] + 2 * a[i];

  ans = n + 1;
  dfsRight(midPos, 0, 0);

  if (ans == n + 1)
    cout << -1;
  else
    cout << ans;

  return 0;
}