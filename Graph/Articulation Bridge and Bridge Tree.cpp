/**
 * @file We_Need_More_Bosses.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-12-13
 * @copyright Copyright (c) 2024
 * @tags : articulationBridge bridge bridges tree dfs bridgetree
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;


struct articulationBridge{
    int n, Time = 0;
    vector<vector<int>> adj, bridgeTree;
    vector<int> disc, low, rnk, p;
    vector<pair<int, int>> br;
    int brRoot;
    articulationBridge(){}
    // constructor - construct everything...
    articulationBridge(vector<vector<int>> &g, int n) : adj(g), n(n), disc(n+10), low(n+10), p(n+10), rnk(n+10){
        Time = 0;
        for(int i=1;i<=n;i++) {
            p[i] = i;
            rnk[i] = 1;
        }
        for (int u = 1; u <= n; u++) {
            if (!disc[u]) dfsBR(u, 0);
        }
    }
    // get parents of node...
    int get(int x){
        return (p[x] == x ? x : p[x] = get(p[x]));
    }
    // link two nodes if no bridge between them...
    void link(int x, int y){ 
        x = get(x);
        y = get(y);
        if(x == y) return;
        if(rnk[x] > rnk[y])
            swap(x, y);
        p[x] = y;
        rnk[y] += rnk[x];	
    }
    // dfs for find bridge...
    int dfsBR(int u, int p) {
        low[u] = disc[u] = ++Time;
        for (int& v : adj[u]) {
            if (v == p) continue;

            if (!disc[v]) {
                dfsBR(v, u);
                if (disc[u] < low[v]){
                    br.push_back({u, v});
                } else {
                    link(u, v);
                }
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    // build bridge tree from bridges...
    void build_brigeTree(){
        bridgeTree.resize(n+10);
        for(auto bridge : br){
            int u = get(bridge.first);
            int v = get(bridge.second);
            bridgeTree[u].push_back(v);
            bridgeTree[v].push_back(u);
            brRoot = u;
        }
    }
};

int farthest(int s, int n, vector<int> &d, vector<vector<int>>&g) {
    static const int inf = N;
    d.assign(n + 1, inf); d[s] = 0;
    vector<bool> vis(n + 1);
    queue<int> q; q.push(s);
    vis[s] = 1; int last = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
            if (vis[v]) continue;
            d[v] = d[u] + 1;
            q.push(v); vis[v] = 1;
        }
        last = u;
    }
    return last;
}

void solve(){

    int n, m; cin >> n >> m;
    vector<vector<int>>g(n+10), bg(n+10);
    for(int i=0;i<m;i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    articulationBridge ab(g, n);
    ab.build_brigeTree();
    vector<int> d;
    // finding distance from 1.
    int x = farthest(ab.brRoot, n, d, ab.bridgeTree);
    // finding distance from x which is fartest from 1.
    int y = farthest(x, n, d, ab.bridgeTree);

    cout << d[y] << endl;

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