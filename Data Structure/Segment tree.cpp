/*
 * @file 07.01 Segment tree.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 * @problem:    Implementing Iterative Segment Tree.
 * @approach:
 * @explanation:
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int a[N];
int tree[4*N];
int n;

// Building Segment Tree...
void build(){
    for(int i=0;i<n;i++){
        tree[n+i] = a[i];
    }

    for(int i=n-1;i>=1;i--){
        tree[i] = tree[i<<1] + tree[i<<1|1];
    }
}


// sum of interval [l, r)
int query(int l, int r){
    int res = 0;
    for(l+=n, r+=n; l<r; l >>=1 , r >>=1 ) {
        if(l&1) res += tree[l++];
        if(r&1) res += tree[--r];
    }
    return res;
}

// set value at position p = value...
void modify(int p, int value){
    for(tree[p+=n] = value; p>1; p >>= 1){
        tree[p>>1] = tree[p] + tree[p^1];
    }
}

// add value to all elements in interval [l, r)
void update(int l, int r, int value){
    for(l += n, r += n; l < r; l >>=1 , r >>= 1){
        if(l&1) tree[l++] += value;
        if(r&1) tree[--r] += value;
    }
}


// pushing all the modifications to the leaves...
// we can treaverse element starting with index n.
// we can get value in o(n).
void push(){
    for(int i=1;i<n;i++){
        tree[i<<1] += tree[i];
        tree[i<<1|1] += tree[i];
        tree[i] = 0;
    }
}


int main(){
    cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    int x = log2(n);
    n = (1 << (x+1));
    // cout << n << endl; 


    build();
    int q; cin >> q;
    cout << q << endl;
    for(int i=0;i<q;i++){
        int l,r; cin >> l >> r;
        l--;
        cout << query(l, r) << endl;
    }
}