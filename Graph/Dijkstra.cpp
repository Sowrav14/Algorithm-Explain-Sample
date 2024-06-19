/*
 * @file Dijkstra.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-19
 * @copyright Copyright (c) 2024
 * @problem: https://cses.fi/problemset/task/1671
 * @approach: Dijkstras Algorithms.
 * @explanation:
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define pii pair<int,int>
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
const int inf = 1e18;
vector<pii>g[N];
int n,m;

void Dijkstras(int s, vector<int>&d, vector<int>&cnt){
    d.resize(n+10, inf), cnt.resize(n+10, 0);
    vector<bool>vis(n+10, 0);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    d[s] = 0; cnt[s] = 1;

    while(!q.empty()){
        pii x = q.top();
        q.pop();
        int u = x.second;
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto y : g[u]){
            int v = y.first;
            int w = y.second;
            if(d[u] + w < d[v]){
                d[v] = d[u] + w;
                q.push({d[v], v});
                cnt[v] = cnt[u];
            } else if(d[u] + w == d[v]){
                cnt[v] = cnt[v] + cnt[u];
            }
        }

    }
}

void solve(){

    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        // g[v].push_back({u, w});
    }

    vector<int>d, c; // shortest distance and number of shortest path from source.
    Dijkstras(1, d, c);
    for(int i=1;i<=n;i++){
        cout << d[i] << " "; 
    } cout << endl;

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