#include<bits/stdc++.h>
using namespace std;

int n;
vector<int>bit;

// updating a single value in bit
void update(int idx, int val){
    while(idx <= n){
        bit[idx] += val;
        idx += (idx) & (-idx);  // lsb will be added.
    }
}

// return sum of (1 - idx)
int query(int idx){
    int ret = 0;
    while(idx > 0){
        ret += bit[idx];
        idx -= (idx) & (-idx);  // lsb will be substracted.
    }
    return ret;
}



int main(){
    cin >> n;
    bit.resize(n+1, 0);
    vector<int>a(n+1);
    for(int i=1;i<=n;i++){
        int x; cin >> x;
        a[i] = x;
        update(i, x);       // initializing bit with formal array values
    }
    int q; cin >> q;
    for(int i=1;i<=q;i++){
        int t,l,r; cin >> t >> l >> r;
        if(t == 2){
            cout << query(r) - query(l-1) << endl;  // just like prefix sum.
        } else {
            update(l, -a[l]);                       // resetting previous
            update(l, r);                           // setting new
        }
    }
}