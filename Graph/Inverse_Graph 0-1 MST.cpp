/*
 * @file Inverse_Graph 0-1 MST.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-15
 * @copyright Copyright (c) 2024
 * @problem: 0-1 MST https://codeforces.com/problemset/problem/1242/B
 * @approach: Inverse Graph with Pie for a Pie technique
 * @explanation: https://codeforces.com/blog/entry/93652
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

vector<set<int>> g;     // store the graph.
set<int> to_remove;     // track unvisited node.

void bfs(int source){
    queue<int>q;
    q.push(source);
    to_remove.erase(source);        // similar work as visited array

    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        vector<int>adj;             // calculate adjacent node with 0 weight
        for(auto it : to_remove){   
            if(!g[u].count(it)){    // if i'th unvisited node is not adj.(weight = 0) to the current node
                adj.push_back(it);  // then connect it 
            }
        }
        for(auto it : adj){
            to_remove.erase(it);    // adjacent node (weight = 0) visited
            q.push(it);             // bfs work.
        }
    }
}


void solve(){

    int n,m; cin >> n >> m;
    g.resize(n+10);
    for(int i=0;i<m;i++){
        int u, v; cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    // all nodes are unvisited initially.
    for(int i=1;i<=n;i++) to_remove.insert(i);
    int cc = 0;                                 // count of connected components

    for(int i=1;i<=n;i++){
        // if i'th node is unvisited then run a bfs from this and find the cc around it.
        if(to_remove.count(i)){
            cc++;
            bfs(i);
        }
    }

    cout << cc - 1 << endl;

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