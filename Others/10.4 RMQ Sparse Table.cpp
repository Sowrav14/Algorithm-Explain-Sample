/*
 * @file RMQ Sparse Table.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-03-20
 * @copyright Copyright (c) 2024
 * @problem: CSES Static Range Minimum Queries.
 * @approach: Sparse Table.
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const int N = 2e5+10;
const int M = 64;
int look[N][M];
int a[N];

/*
    look[i][j] = min in range i to size of (1 << j) i.e. (a[i] to a[i + (1 << j) - 1])
    ex. look[2][3] = min in range 2 to size 8 (a[2] to a[9])
 */

void build(int sz){
    // look[i][0] = (a[i] to a[i]) = 0
    for(int i=1;i<=sz;i++){
        look[i][0] = a[i];
    }
    // iterate j from size 1 to log(sz).
    for(int j = 1; (1 << j) <= sz; j++){
        // size 2^j
        // iterate for all starting i.
        for(int i = 1; (i + (1 << j) - 1) <= sz; i++){
            // (a[1]-a[8]) = min(a[1]-a[4], a[5]-a[8])
            look[i][j] = min(look[i][j - 1], look[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r){
    int i = l; // starting of range
    int j = (int)(log2(r - l + 1)); // size of range
    int k = r - (1 << j) + 1; // starting of second range.
    // (a[2]-a[10]) = min(a[2]-a[9], a[3]-a[10])
    return min(look[i][j], look[k][j]);
}

void solve(){

    int n; cin >> n;
    int q; cin >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    build(n);
    while(q--){
        int l,r; cin >> l >> r;
        cout << query(l, r) << endl;
    }

}


signed main(){
    Fast_IO()
    int t = 1;
    // cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}