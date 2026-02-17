#include <bits/stdc++.h>
using namespace std;

// 2025.11.26 
// tag: 分治 O(nlogn)
// solution：二分答案

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, n, m;
    cin >> l >> n >> m;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }

    int left = 0, right = l;
    while(left <= right){
        int cnt = 0,prepos=0,mid=(left+right)/2;
        for(int curpos:pos){
            if(curpos-prepos<mid){
                cnt++;
            }else
                prepos = curpos;
        }

        if (l - prepos < mid) cnt++;
        if(cnt<=m){
            left = mid + 1;
        }else
            right = mid - 1;
    }

    cout << left-1 << endl;
    return 0;
}