#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
  char data;
  shared_ptr<Node> left;
  shared_ptr<Node> right;

  Node(char d) : data(d), left(nullptr), right(nullptr) {}
  Node() : data('\0'), left(nullptr), right(nullptr) {}
};

unordered_map<string, char> dict;

shared_ptr<Node> rebuildHuffmanTree(const string &s, int &index) {
  if (index >= s.length())
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

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node> &root, string prefix = "") {
  if (!root)
    return;

  if (root->data != '\0') {
    cout << "Leaf: " << root->data << " code: " << prefix << endl;
    dict[prefix] = root->data;
  }
  printTree(root->left, prefix + "0");
  printTree(root->right, prefix + "1");
}

string change(char c) {
  int val;
  if (c >= 'a' && c <= 'f')
    val = 10 + c - 'a';
  else if (c >= '0' && c <= '9')
    val = c - '0';

  string cur = "";
  for (int i = 3; i >= 0; i--) {
    cur += (val >> i) & 1 ? '1' : '0';
  }
  return cur;
}

string decode(string s) {
  s.erase(0, 1);
  int zero = 0, idx = 1;
  while (s.back() != '0') {
    zero += idx * (s.back() - '0');
    s.pop_back();
    idx *= 10;
  }
  s.pop_back();
  cout << zero << " " << s << endl;

  string bit_str = "";
  for (char c : s)
    bit_str += change(c);

  for (int i = 1; i <= zero; i++) {
    bit_str.pop_back();
  }
  cout << bit_str << endl;

  string cur, ans;
  for (char c : bit_str) {
    cur += c;
    if (dict.count(cur)) {
      ans += dict[cur];
      cur = "";
    }
  }
  cout << ans;
  return ans;

}

int main() {
  string encodedTree = "001b01c1d1a"; // 示例：0表示内部节点，1表示叶子节点
  int index = 0;
  auto root = rebuildHuffmanTree(encodedTree, index);

  cout << "Rebuilt Huffman Tree:" << endl;
  printTree(root);

  string ss = "H898007";
  decode(ss);


  return 0;
}