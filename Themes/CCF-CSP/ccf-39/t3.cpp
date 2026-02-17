#include <bits/stdc++.h>
using namespace std;

struct HTTPdata {
    string key, value;
    HTTPdata(const string& k, const string& v) : key(k), value(v) {
    }
};
deque<HTTPdata> dList;
int s, d;

string& cut(string& s) {
    if (s.length() < 2 || s[0] != 'H') return s;
    if (s[0] == 'H' && s[1] == 'b') 
    if (s[0] == 'H' && s[1] == 'H') s.erase(0, 1);
    return s;
}

void insert(string& k, string& v) {
    if (dList.size() < d) {
        dList.emplace_front(k, v);
    } else {  // to be continue
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> d;
    dList.resize(d);
    vector<HTTPdata> sList;
    string k, v;
    for (int i = 0; i < s; i++) {
        cin >> k >> v;
        sList.emplace_back(cut(k), cut(v));
    }
    string huffman_code;
    cin >> huffman_code;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int choose, idx;
        cin >> choose;
        if (choose == 1) {
            cin >> idx;
            cout << sList[idx - 1].key << ": " << sList[idx - 1].value << endl;
        } else if (choose == 3) {
            cin >> idx;
            if (idx == 0) {
                cin >> k >> v;
                cout << cut(k) << ": " << cut(v) << endl;
            } else {
                cin >> v;
                if(idx<=s)
                cout << sList[idx - 1].key << ": " << cut(v) << endl;
                else
                    cout << dList[idx - 1 - s].key << ": " << cut(v) << endl;
            }
        } else if (choose == 2) {
            cin >> idx;
            if (idx == 0) {
                cin >> k >> v;
                cout << cut(k) << ": " << cut(v) << endl;
                insert(k, v);
            } else {
                cin >> v;
                cout << sList[idx - 1].key << ": " << cut(v) << endl;
                insert(k, v);
            }
        }
    }
    return 0;
}