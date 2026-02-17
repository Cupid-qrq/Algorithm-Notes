#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, string> coding;

struct Node {
    char data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {
    }
    Node() : data('\0'), left(nullptr), right(nullptr) {
    }
};

shared_ptr<Node> rebuildHuffmanTree(const string& s, int& index) {
    if (index >= s.length()) return nullptr;

    if (s[index] == '1') {
        index++;               // 跳过'1'
        char ch = s[index++];  // 读取字符
        return make_shared<Node>(ch);
    } else if (s[index] == '0') {
        index++;  // 跳过'0'
        auto node = make_shared<Node>();
        node->left = rebuildHuffmanTree(s, index);
        node->right = rebuildHuffmanTree(s, index);
        return node;
    }
    return nullptr;
}

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node>& root, string prefix = "") {
    if (!root) return;

    if (root->data != '\0') {
        // cout <<  "Leaf: " << root->data <<"code: "<<prefix<< endl;
        coding[root->data] = prefix;
    }
    printTree(root->left, prefix + "0");
    printTree(root->right, prefix + "1");
}

int main() {
    string encodedTree = "001b01c1d1a";  // 示例：0表示内部节点，1表示叶子节点
    int index = 0;
    auto root = rebuildHuffmanTree(encodedTree, index);

    printTree(root);
    for (auto& [c, code] : coding) cout << c << ": " << code << endl;

    return 0;
}