/**
 * @file 12.02 count_of_inversion_segment_tree.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.3
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 * @problem: Count of Inversion in array
 * @approach: Segment tree
 * @explanation:
 *              each node of segment tree will contain number of element in that range.
 *              a node of range[i..j] = no_of_element(i<=x<=j)
 *              iterate a[i] count how many no are in range a[i]+1 to max.
 *              update that element in segment tree.
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2*1e5+10;
int tree[4*N];

// updating range[i...j] that contain id by 1.
void update(int node, int i, int j, int id){
    if(id < i or id > j) return;
    if(i == j) {
        tree[node] += 1;
        return;
    }
    int m = (i + j)/2;
    update(2*node, i, m, id);
    update(2*node+1, m+1, j, id);
    tree[node] = tree[2*node] + tree[2*node+1];
    return;
}

// get count for range[l...r]
int query(int node, int i, int j, int l, int r){
    if(i > r or j < l) return 0;
    if(i >= l and j <= r) return tree[node];

    int m = (i + j) / 2;
    int left = query(2*node, i, m, l, r);
    int right = query(2*node+1, m+1, j, l, r);
    return left + right;
}

void solve(){

    int n; cin >> n;
    for(int i=0;i<=4*n;i++) tree[i] = 0;
    int inv = 0;
    for(int i=1;i<=n;i++){
        int x; cin >> x;
        // cout << query(1, 1, n, x, n) << " ";
        inv += query(1, 1, n, x, n);    // get no of element in right side.
        update(1, 1, n, x);             // updating current element.
    }
    cout << inv << endl;
    
}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}