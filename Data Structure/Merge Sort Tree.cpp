// https://www.spoj.com/problems/KQUERY/
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const int N = 30010;
int a[N];
vector<int> tree[4*N];



void build(int node, int l, int r){
    if(l == r){
        tree[node].push_back(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2*node, l, m);
    build(2*node+1, m+1, r);
    merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), back_inserter(tree[node]));
    return;
}

int query(int node, int l, int r, int i, int j, int k){
    
    if(l>j or r<i){
        return 0;
    }
    if(l>=i and r<=j){
        int x = upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
        return tree[node].size() - x;
    }
    int m = (l + r) / 2;
    int left = query(2*node, l, m, i, j, k);
    int right = query(2*node+1, m+1, r, i, j, k);
    return left + right;
}


void solve(){

    int n; cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    build(1, 1, n);
    
    // tree is ok.
    // for(int i=1;i<10;i++){
    //     cout << i << " [ ";
    //     for(auto it : tree[i]) cout << it << " ";
    //     cout << " ]" << endl;
    // }


    int q; cin >> q;
    for(int i=1;i<=q;i++){
        int l, r, k; cin >> l >> r >> k;
        cout << query(1, 1, n, l, r, k) << endl;
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