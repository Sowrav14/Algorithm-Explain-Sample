/*
 * @file SCC Kosaraju's Algorithm.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-07-13
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/gym/103960/problem/H
 * @approach:
 * @explanation: https://www.shafaetsplanet.com/?p=2531
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5+10;
bool vis[N];
vector<int> g[N], r[N], G[N], vec; //G is the condensed graph
int idx[N], in[N], out[N];

// extract the topological ordering (vec).
void dfs1(int u) {
    vis[u] = 1;
    for(auto v : g[u]) if(!vis[v]) dfs1(v);
    vec.push_back(u);
}

// extract connected components separately...
vector<int> comp;
void dfs2(int u) {
    comp.push_back(u);
    vis[u] = 1;
    for(auto v: r[u]) if(!vis[v]) dfs2(v);
}

void solve(){

    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        r[v].push_back(u);  // reverse edge.
    }
    // run dfs to find the topological ordering.
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs1(i);
    reverse(vec.begin(), vec.end());

    // run dfs by the topological order to find strongly connected components from the graph using inverse graph
    memset(vis, 0, sizeof vis);
    int scc = 0;
    for(auto u: vec) {
        if(!vis[u]) {
            comp.clear();
            dfs2(u);
            scc++;
            for(auto x: comp) idx[x] = scc;
        }
    }
    // we get idx[i] = j where ith node belongs to jth scc.
    // there is total (scc) total scc.

    // building the condense graph...
    for(int u = 1; u <= n; u++) {
        for(auto v: g[u]) {
            if(idx[u] != idx[v]) {  // doesn't belongs to same scc
                in[idx[v]]++, out[idx[u]]++;
                G[idx[u]].push_back(idx[v]);    // edge added in condense graph
            }
        }
    }


    // if the graph is tree then every node must have at least one indegree and outdegree
    // to be strongly connected. Here condense graph is obviously a tree. so we can get
    // how many edge to add to make condense graph scc.
    int needed_in=0, needed_out=0;
    for(int i = 1; i <= scc; i++) {
        if(!in[i]) needed_in++;
        if(!out[i]) needed_out++;
    }
    int ans = max(needed_in, needed_out);
    if(scc == 1) ans = 0;
    cout << ans << '\n';

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