/*
 * @file 10.5 K_th_Number.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-04-17
 * @copyright Copyright (c) 2024
 * @problem: find kth number in a range(l, r) after sorting the range...
 * @approach: merge_sort tree
 * @explanation: 
 *               https://onedrive.live.com/view.aspx?resid=EC977D2876C10C5A%2117142&id=documents&wd=target%28Practice.one%7CDEDAEE68-11D0-411F-8049-DD8905DC9174%2FKth%20number%20by%20MST%7CDF5F08A3-4DCF-401C-82DC-AFE945DE7721%2F%29
                 onenote:https://d.docs.live.net/ec977d2876c10c5a/Documents/Competitive%20Programming/Practice.one#Kth%20number%20by%20MST&section-id={DEDAEE68-11D0-411F-8049-DD8905DC9174}&page-id={DF5F08A3-4DCF-401C-82DC-AFE945DE7721}&end
 */



#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
int a[N];
pair<int,int>arr[N];
vector<int> tree[4*N];


void build(int node, int l, int r){
    if(l == r) {
        tree[node].push_back(arr[l].second);
        return;
    }
    int m = (l + r) / 2;
    build(2*node, l, m);
    build(2*node+1, m+1, r);
    
    merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), back_inserter(tree[node]));
}

int query(int node, int l, int r, int i, int j, int k){
    if(l == r) return tree[node][0];
    int m = (l + r) / 2;
    int cnt = upper_bound(tree[2*node].begin(), tree[2*node].end(), j) - lower_bound(tree[2*node].begin(), tree[2*node].end(), i);
    if(cnt >= k){
        return query(2*node, l, m, i, j, k);
    } else{
        return query(2*node+1, m+1, r, i, j, k-cnt);
    }
}


void solve(){

    int n,q; cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i], arr[i] = {a[i], i};
    sort(arr+1, arr+n+1);
    build(1, 1, n);

    // tree ok.
    // for(int i=1;i<=25;i++){
    //     cout << i << " -- ";
    //     for(auto it : tree[i]){
    //         cout << it << " ";
    //     } cout << endl;
    // }

    for(int i=1;i<=q;i++){
        int l,r,k; cin >> l >> r >> k;
        cout << a[query(1, 1, n, l, r, k)] << endl;
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