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


// updating a single value in bit
void update(int idx, int val, vector<int>&bit, int n){
    while(idx <= n){
        bit[idx] += val;
        idx += (idx) & (-idx);  // lsb will be added.
    }
}

// return sum of (1 - idx)
int query(int idx, vector<int>&bit, int n){
    int ret = 0;
    while(idx > 0){
        ret += bit[idx];
        idx -= (idx) & (-idx);  // lsb will be substracted.
    }
    return ret;
}



void solve(){
    int n; cin >> n;
    vector<int>bit(n+10, 0);
    
    int u; cin >> u;
    while(u--){
        int l,r,val; cin >> l >> r >> val;
        l++, r++;
        update(l, val, bit, n);         // updating [l, ...] with incrementing
        update(r+1, -val, bit, n);      // updating [r+1, ...] with decrementing
    }

    int q; cin >> q;
    while(q--){
        int idx; cin >> idx;
        idx++;
        cout << query(idx, bit, n) << endl;
    }
}

int main(){
    int t; cin >> t;
    while(t--){
        solve();
    }
}