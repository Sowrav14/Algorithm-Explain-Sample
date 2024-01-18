/**
 * @file 11.2 Update_the_array.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 *          Spoj - Update the array using bit...
 */


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



void solve(){
    cin >> n;
    bit.resize(n+1, 0);
    
    int u; cin >> u;
    while(u--){
        int l,r,val; cin >> l >> r >> val;
        l++, r++;
        update(l, val);
        update(r+1, -val);
    }

    int q; cin >> q;
    while(q--){
        int idx; cin >> idx;
        cout << query(idx) << endl;
    }
}

int main(){
    int t; cin >> t;
    while(t--){
        solve();
    }
}