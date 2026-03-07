#include <bits/stdc++.h>
using namespace std;

struct HTTPdata {
  string key, value;
  HTTPdata(const string &k, const string &v) : key(k), value(v) {}
};

struct Node {
  char data;
  shared_ptr<Node> left;
  shared_ptr<Node> right;

  Node(char d) : data(d), left(nullptr), right(nullptr) {}
  Node() : data('\0'), left(nullptr), right(nullptr) {}
};

shared_ptr<Node> rebuildHuffmanTree(const string &s, int &index) {
  if (index >= (int)s.length())
    return nullptr;

  if (s[index] == '1') {
    index++;              // 跳过'1'
    char ch = s[index++]; // 读取字符
    return make_shared<Node>(ch);
  } else if (s[index] == '0') {
    index++; // 跳过'0'
    auto node = make_shared<Node>();
    node->left = rebuildHuffmanTree(s, index);
    node->right = rebuildHuffmanTree(s, index);
    return node;
  }
  return nullptr;
}

shared_ptr<Node> huffmanRoot;
deque<HTTPdata> dList;
int s, d;

inline int hexValue(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return 10 + c - 'a';
  return 10 + c - 'A';
}

string decode(const string &encoded) {
  if (!huffmanRoot || encoded.size() < 3)
    return "";

  int len = (int)encoded.size();
  int p = hexValue(encoded[len - 2]) * 16 + hexValue(encoded[len - 1]);
  int dataHexLen = len - 3;
  int totalBits = dataHexLen * 4 - p;
  if (totalBits <= 0)
    return "";

  string ans;
  ans.reserve(totalBits / 2);
  auto cur = huffmanRoot;
  int usedBits = 0;

  for (int i = 1; i <= dataHexLen && usedBits < totalBits; ++i) {
    int val = hexValue(encoded[i]);
    for (int bit = 3; bit >= 0 && usedBits < totalBits; --bit) {
      if (!cur)
        return ans;
      cur = ((val >> bit) & 1) ? cur->right : cur->left;
      ++usedBits;
      if (cur && cur->data != '\0') {
        ans.push_back(cur->data);
        cur = huffmanRoot;
      }
    }
  }

  return ans;
}

string cut(const string &s) {
  if (s.length() < 2 || s[0] != 'H')
    return s;

  if (s[1] == 'H')
    return s.substr(1);

  return decode(s);
}

void insert(string k, string v) {
  if ((int)dList.size() == d)
    dList.pop_back();

  dList.emplace_front(k, v);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s >> d;
  vector<HTTPdata> sList;
  sList.reserve(s);
  string k, v;
  for (int i = 0; i < s; i++) {
    cin >> k >> v;
    sList.emplace_back(k, v);  // 静态表直接存原始字符串，不解码
  }

  string encodedTree;
  cin >> encodedTree;
  int index = 0;
  huffmanRoot = rebuildHuffmanTree(encodedTree, index);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int choose, idx;
    cin >> choose;
    if (choose == 1) {
      cin >> idx;
      if (idx <= s)
        cout << sList[idx - 1].key << ": " << sList[idx - 1].value << '\n';
      else
        cout << dList[idx - s - 1].key << ": " << dList[idx - s - 1].value
             << '\n';
    }

    else if (choose == 2) {
      cin >> idx;
      if (idx == 0) {
        cin >> k >> v;
        k = cut(k);
        v = cut(v);
        cout << k << ": " << v << '\n';
        insert(k, v);
      } else {
        cin >> v;
        if (idx <= s)
          k = sList[idx - 1].key;
        else
          k = dList[idx - s - 1].key;

        v = cut(v);
        cout << k << ": " << v << '\n';
        insert(k, v);
      }

    }

    else if (choose == 3) {
      cin >> idx;
      if (idx == 0) {
        cin >> k >> v;
        cout << cut(k) << ": " << cut(v) << '\n';
      } else {
        cin >> v;
        if (idx <= s)
          k = sList[idx - 1].key;
        else
          k = dList[idx - s - 1].key;
        cout << k << ": " << cut(v) << '\n';
      }
    }
  }
  return 0;
}