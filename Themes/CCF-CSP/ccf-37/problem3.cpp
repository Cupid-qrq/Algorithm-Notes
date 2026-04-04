#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007LL;

struct Operand {
  bool isVarRef = false; // true: $var, false: literal
  int value = 0;         // varId or literal length(mod MOD)
};

struct Node {
  bool hasValue = false; // 是否已经是最终值
  ll valueLen = 0;       // 最终值长度（取模）
  vector<Operand> expr;  // 延迟求值时保存表达式
};

unordered_map<string, int> idOf;
vector<Node> vars;
vector<int> seenStamp;
vector<ll> memoLen;
int curStamp = 1;

int getVarId(const string &name) {
  auto it = idOf.find(name);
  if (it != idOf.end())
    return it->second;
  int id = (int)vars.size();
  idOf[name] = id;
  vars.push_back(Node());
  seenStamp.push_back(0);
  memoLen.push_back(0);
  return id;
}

ll evalVar(int varId);

// token 规则：
// "$x" -> 取变量 x 的值长度
// "abc" -> 字面串长度
ll evalToken(const Operand &op) {
  if (op.isVarRef)
    return evalVar(op.value);
  return op.value;
}

// 计算变量值长度；间接赋值变量每次在当前环境下重新求值
ll evalVar(int varId) {
  if (seenStamp[varId] == curStamp)
    return memoLen[varId];

  Node &cur = vars[varId];
  ll res = 0;
  if (cur.hasValue) {
    res = cur.valueLen;
  } else {
    for (const Operand &op : cur.expr) {
      res += evalToken(op);
      if (res >= MOD)
        res %= MOD;
    }
    res %= MOD;
  }

  seenStamp[varId] = curStamp;
  memoLen[varId] = res;
  return res;
}

vector<string> splitLine(const string &line) {
  vector<string> out;
  int n = (int)line.size();
  int i = 0;
  while (i < n) {
    while (i < n && line[i] == ' ')
      ++i;
    if (i >= n)
      break;
    int j = i;
    while (j < n && line[j] != ' ')
      ++j;
    out.push_back(line.substr(i, j - i));
    i = j;
  }
  return out;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  idOf.reserve((size_t)n * 2 + 16);
  vars.reserve((size_t)n * 2 + 16);
  seenStamp.reserve((size_t)n * 2 + 16);
  memoLen.reserve((size_t)n * 2 + 16);

  while (n--) {
    string line;
    getline(cin, line);
    vector<string> parts = splitLine(line);
    if (parts.empty())
      continue;

    int op = parts[0][0] - '0';
    int varId = getVarId(parts[1]);

    if (op == 1) {
      // 直接赋值：立即求值并覆盖旧定义
      ++curStamp;
      if (curStamp == INT_MAX) {
        fill(seenStamp.begin(), seenStamp.end(), 0);
        curStamp = 1;
      }

      ll res = 0;
      for (int i = 2; i < (int)parts.size(); ++i) {
        const string &tok = parts[i];
        if (!tok.empty() && tok[0] == '$') {
          int depId = getVarId(tok.substr(1));
          res += evalVar(depId);
        } else {
          res += (ll)tok.size() % MOD;
        }
        if (res >= MOD)
          res %= MOD;
      }
      Node &nd = vars[varId];
      nd.hasValue = true;
      nd.valueLen = res % MOD;
      nd.expr.clear();
    } else if (op == 2) {
      // 间接赋值：只保存表达式并覆盖旧定义
      Node &nd = vars[varId];
      nd.hasValue = false;
      nd.valueLen = 0;
      nd.expr.clear();
      nd.expr.reserve(parts.size() > 2 ? (size_t)parts.size() - 2 : 0);
      for (int i = 2; i < (int)parts.size(); ++i) {
        const string &tok = parts[i];
        if (!tok.empty() && tok[0] == '$') {
          int depId = getVarId(tok.substr(1));
          nd.expr.push_back({true, depId});
        } else {
          nd.expr.push_back({false, (int)((ll)tok.size() % MOD)});
        }
      }
    } else if (op == 3) {
      // 输出变量值长度 mod MOD
      ++curStamp;
      if (curStamp == INT_MAX) {
        fill(seenStamp.begin(), seenStamp.end(), 0);
        curStamp = 1;
      }
      cout << evalVar(varId) % MOD << '\n';
    }
  }

  return 0;
}
