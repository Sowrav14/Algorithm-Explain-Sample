/**
 * @file Persistent Segment Tree.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-10-10
 * @copyright Copyright (c) 2024
 * @problem: https://cses.fi/problemset/task/1737/
 * @approach: Persistent Segment Tree
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N = 2e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;


struct PST {
    #define lc t[cur].l
    #define rc t[cur].r

    // defining node for segment tree...
    struct node {
        int l = 0, r = 0, val = 0;
    } t[40 * N];
    // arrays to store given values and roots of each version of st.
    int arr[N], root[N];

    // initialized without values. return root[0]
    // OR 
    //with values from arr (array). return root[1]
    int T = 0;
    int build(int b, int e) {
        int cur = ++T;
        if (b == e){
            t[cur].val = arr[b];
            return cur;
        }
        int mid = b + e >> 1;
        lc = build(b, mid);
        rc = build(mid + 1, e);
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }


    // update single value in cur version of st with creating and returning new version.
    int p_update(int pre, int b, int e, int i, int v){
        int cur = ++T;
        t[cur] = t[pre];
        if (b == e){
            t[cur].val = v;        // add.
            return cur;
        }

        int mid = b + e >> 1;
        if (i <= mid){
            rc = t[pre].r;
            lc = p_update(t[pre].l, b, mid, i, v);
        } else {
            lc = t[pre].l;
            rc = p_update(t[pre].r, mid + 1, e, i, v);
        }
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }

    // update single value in cur version of st without creating new version.
    // would affect several version ***
    void update(int cur, int b, int e, int i, int v){
        if(b > i or e < i) return;
        if(b == e){
            t[cur].val = v;
            return;
        }

        int m = (b + e) / 2;
        update(lc, b, m, i, v);
        update(rc, m+1, e, i, v);
        t[cur].val = t[lc].val + t[rc].val;
        return;
    }

    // get kth updated note from transitioning to pre to cur.
    int query(int pre, int cur, int b, int e, int k){
        if (b == e){
            return b;
        }
        int cnt = t[lc].val - t[t[pre].l].val;
        int mid = b + e >> 1;
        if (cnt >= k)
            return query(t[pre].l, lc, b, mid, k);
        else
            return query(t[pre].r, rc, mid + 1, e, k - cnt);
    }

    // get sum of (i->j) in the cur version 
    int query_sum(int cur, int b, int e, int i, int j){
        if(e < i or b > j) return 0;
        if(b>=i and e<=j) return t[cur].val;

        int m = (b + e) / 2;
        int left = query_sum(t[cur].l, b, m, i, j);
        int right = query_sum(t[cur].r, m+1, e, i, j);
        return left + right;
    }
} pst;


/** Persistent Segment Tree
 *  Given Array [ 2 , 3, 1, 2, 5]
 *  query-type-1 given-> k a b get sum for range [a, b] fo kth array
 *  query-type-2 given-> k i x set value of ith in kth array to x
 *  query-type-3 given-> k  make of copy of kth array append to last
 **/


void solve(){

    map<int, int>mp;
    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> pst.arr[i];
    
    pst.root[1] = pst.build(1, n);
    // pst.root[2] = pst.p_update(pst.root[1], 1, n, 1, pst.arr[1]);
    // pst.root[2] = pst.p_update(pst.root[2], 1, n, 3, 2);
    // // pst.update(pst.root[2], 1, n, 1, 9);
    // cout << pst.query_sum(pst.root[1], 1, n, 2, 5) << endl;
    int cnt = 1;
    while(q--){
        int t, k; cin >> t >> k;
        if(t == 1){
            int a, x ; cin >> a >> x;
            pst.root[k] = pst.p_update(pst.root[k], 1, n, a, x);
        } else if(t == 2){
            int l, r; cin >> l >> r;
            cout << pst.query_sum(pst.root[k], 1, n, l, r) << endl;
        } else{
            cnt++;
            pst.root[cnt] = pst.root[k];
        }
    }

}

signed main() {
    Fast_IO() 
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++){
        // cout << "Case #" << i << ": ";
        solve();
    }
}