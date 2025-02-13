/*
 * @file Dijkstra + Segment Tree.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-21
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/contest/786/problem/B
 * @approach: Segment Tree + Dijkstra on Dense graph.
 * @explanation: https://codeforces.com/blog/entry/51163
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define pii pair<int,int>
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int inf = 1e18;
int ver[2][4 * N];	// 0: to [l, r], 1: from [l, r]
vector<pii> adj[9 * N];
int n, m, s, nx;

// build the segment tree...
void build(int t, int id = 1, int l = 0, int r = n){
    // indexing the segment tree to make a proper graph with original graph.
	ver[t][id] = nx ++;
	if(r - l < 2){
        // make a connection to child of segment tree to corresponding node of original graph
		if(!t)
			adj[ver[t][id]].push_back({l, 0});
		else
			adj[l].push_back({ver[t][id], 0});
		return ;
	}
	int mid = (l + r) >> 1;
	build(t, 2*id, l, mid);
	build(t, 2*id+1, mid, r);
    // make a connection to internal node to corresponding child node...
	if(!t)
		adj[ver[t][id]].push_back({ver[t][2*id], 0}),
		adj[ver[t][id]].push_back({ver[t][2*id+1], 0});
	else
		adj[ver[t][2*id]].push_back({ver[t][id], 0}),
		adj[ver[t][2*id+1]].push_back({ver[t][id], 0});
}
// to add and edge between v - [x..y] or [x..y] to v
// first find the segment tree nodes equivalent to [x...y]
// add edge between those nodes with v.
void add(int v, int w, int x, int y, int t, int id = 1, int l = 0, int r = n){
	if(x >= r or l >= y)	return ;
	if(x <= l && r <= y){
		if(!t)
			adj[v].push_back({ver[t][id], w});
		else
			adj[ver[t][id]].push_back({v, w});
		return ;
	}
	int mid = (l + r) >> 1;
	add(v, w, x, y, t, 2*id, l, mid);
	add(v, w, x, y, t, 2*id+1, mid, r);
}

// normal dijkstras to return distances(vector) from source(s)
vector<long long> dijkstra(int s) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    vector<int> d(9 * N + 1, inf); vector<bool> vis(9 * N + 1, 0);
    q.push({0, s});
    d[s] = 0;
    while(!q.empty()){
        auto x = q.top(); q.pop();
        int u = x.second;
        if(vis[u]) continue; vis[u] = 1;
        for(auto y: adj[u]){
            int v = y.first; long long w = y.second;
            if(d[u] + w < d[v]){
                d[v] = d[u] + w; q.push({d[v], v});
            }
        }
    }
    return d;
}

void solve(){

    cin >> n >> m >> s;
    s--;
    nx = n;
    build(0), build(1);

    while(m--){
		int t; cin >> t;
		if(t == 1){
			int v, u, w; cin >> v >> u >> w;
			--v, --u;
			adj[v].push_back({u, w});
		}
		else{
			int v, l, r, w; cin >> v >> l >> r >> w;
			--v, --l;
			add(v, w, l, r, t-2);
		}
	}

    vector<int> ans = dijkstra(s);
    for(int i=0;i<n;i++) {
        cout << (ans[i] >= inf ? -1 : ans[i]) << " ";
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