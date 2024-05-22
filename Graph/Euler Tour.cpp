/*
 * @file Euler Tour.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-05-22
 * @copyright Copyright (c) 2024
 * @problem: CSES -> Subtree Queries.
 *              https://cses.fi/problemset/task/1137/
 * @approach: Euler tour
 * @explanation: 
 *                  - find starting time and ending time using dfs.
 *                  - for each node i, every node j whose start[j] is between the
 *                      start[i] - end[i] belongs to the subtree of i.
 *                  - use Fenwick Tree to get_sum[start[i], end[i]) and update(start[i], val)
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5+10;
vector<int>g[N];
int vals[N];
int st[N], fi[N];
int timer = 1;

vector<int>bit;
int tot;


// updating a single value in bit
void update(int idx, int val){
    while(idx <= tot){
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


// dfs for euler tour
// calculate entering time end leaving time of each node...
void dfs(int u, int p){
    st[u] = timer++;
    for(auto v : g[u]){
        if(v != p) dfs(v, u);
    }
    fi[u] = timer;
}


void solve(){

    int n,q; cin >> n >> q;
    tot = 2 * n + 10;
    bit.resize(tot, 0);
    for(int i=1;i<=n;i++) cin >> vals[i];
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    // Initializing the bit.
    // for every start[i] initial value is vals[i]...
    for(int i=1;i<=n;i++){
        update(st[i], vals[i]);
    }
    
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int id, val; cin >> id >> val;
            update(st[id], -vals[id]);
            vals[id] = val;
            update(st[id], vals[id]);
        } else{
            int id; cin >> id;
            // cout << "( " << st[id] << " " << fi[id] <<  " )" << endl;
            cout << query(fi[id]-1) - query(st[id] - 1) << endl;
        }
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