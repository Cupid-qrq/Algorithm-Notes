#include <bits/stdc++.h>
using namespace std;

struct LRU {
  int hotCap, coldCap; // q1=热队列容量n1, q2=冷队列容量n2

  list<int> hot, cold;         // hot=q1, cold=q2; front=最近, back=最久
  unordered_map<int, int> loc; // 1=hot, 2=cold
  unordered_map<int, list<int>::iterator> itr;

  LRU(int n1, int n2) : hotCap(n1), coldCap(n2) {}

  void remove(int p) {
    if (loc[p] == 1)
      hot.erase(itr[p]);
    else
      cold.erase(itr[p]);
    itr.erase(p);
    loc.erase(p);
  }

  void discard(int p) {
    itr.erase(p);
    loc.erase(p);
  }

  void insert(int p) {
    if (!loc.count(p)) {
      // 规则1：不在队列中，插入冷队列首部
      cold.push_front(p);
      itr[p] = cold.begin();
      loc[p] = 2;
      // 冷队列满则淘汰尾部
      if ((int)cold.size() > coldCap) {
        discard(cold.back());
        cold.pop_back();
      }
    } else {
      // 规则2：在队列中，移到热队列首部
      remove(p);
      hot.push_front(p);
      itr[p] = hot.begin();
      loc[p] = 1;
      // 热队列满则淘汰尾部
      if ((int)hot.size() > hotCap) {
        int old = hot.back();
        hot.pop_back();
        // 规则4：仅当冷队列未满时，降级到冷队列首部
        if ((int)cold.size() < coldCap) {
          cold.push_front(old);
          itr[old] = cold.begin();
          loc[old] = 2;
        } else {
          // 冷队列也满，直接丢弃
          discard(old);
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n1, n2, m;
  cin >> n1 >> n2 >> m;
  LRU sql(n1, n2);

  int p;
  while (m--) {
    cin >> p;
    sql.insert(p);
  }

  for (int &x : sql.hot)
    cout << x << " ";
  cout << '\n';
  for (int &x : sql.cold)
    cout << x << " ";

  return 0;
}