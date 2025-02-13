/**
 * @file Centeroid Decomposition.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-10-15
 * @copyright Copyright (c) 2024
 * @topic: Centeroid Decomposition of tree.
 * @see_problems:
 *              - https://cses.fi/problemset/task/2079
 *              - https://codeforces.com/contest/321/problem/C
 *              - https://codeforces.com/contest/342/problem/E
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

int n, root;
vector<int> g[N];
int sz[N];
int tot, done[N], cenpar[N], par[N][20];
// total node, done decomposition, parent of centeroid.

/* Centeroid Decomposition Processing */

/* DFS to calculate size of every subtree */
void calc_sz(int u, int p) {
    tot ++;
    sz[u] = 1;
    for (auto v : g[u]) {
        if(v == p || done[v]) continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

/* find the centeroid */
int find_cen(int u, int p) {
    for (auto v : g[u]) {
        if(v == p || done[v]) continue;
        else if(sz[v] > tot / 2) return find_cen(v, u);
    }
    return u;
}

/* finding centeroids one by one */
void decompose(int u, int pre) {
    tot = 0;
    calc_sz(u, pre);
    int cen = find_cen(u, pre);
    cenpar[cen] = pre;
    done[cen] = 1;
    for(auto v : g[cen]) {
        if(v == pre || done[v]) continue;
        decompose(v, cen);
    }
}

/* Reset the inital tree and construct the decomposed tree */
/* Return the root of centeroid decomposed tree */
void cTree(){
    decompose(1, 0);
    for(int i = 1; i <= n; i++) g[i].clear();
    for(int i = 1; i <= n; i++) {
        g[cenpar[i]].push_back(i);
        g[i].push_back(cenpar[i]);
        if (cenpar[i] == 0) root = i;
    }
}

/* LCA processing */
int dep[N];
void dfs(int u, int pre) {
    dep[u] = dep[pre] + 1;
    par[u][0] = pre;
    for(auto v : g[u]){
        if(v == pre) continue;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u,v);
    for(int k=19;k>=0;k--) if(dep[par[u][k]] >= dep[v])  u = par[u][k];
    if(u == v) return u;
    for(int k=19;k>=0;k--) if(par[u][k] != par[v][k]) u = par[u][k],v = par[v][k];
    return par[u][0];
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u,v)];
}

void initLCA(){
    dfs(1, 0);
    for(int k=1;k<20;k++){
        for(int i=1;i<=n;i++){
            par[i][k] = par[par[i][k-1]][k-1];
        }
    }
}

/* Query Processing */
int ans[N];         // what value should be set??
/* Update node x to red from blue (turn on) */
void update(int x) {
    int u = x;
    while(x){
        ans[x] = min(ans[x], dist(u,x));
        x = cenpar[x];
    }
}

/* Return distance of closest red node from node x */
int query(int x) {
    int ret = inf, u = x;
    while(x){
        ret = min(ret, ans[x] + dist(u,x));
        x = cenpar[x];
    }
    return ret;
}


void solve(){

    cin >> n;
    int q; cin >> q;
    for(int i=1;i<n;i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    initLCA();
    cTree();
    
    for(int i=0;i<=n;i++) ans[i] = inf;
    update(1);

    while(q--){
        int t, x; cin >> t >> x;
        if(t == 1){
            update(x);
        } else {
            cout << query(x) << endl;
        }
    }

}


signed main(){
    Fast_IO()
    int t = 1;
    // cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case #" << i << ": ";
        solve();
    }
}