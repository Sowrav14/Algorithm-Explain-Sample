/*
 * @file MST example1.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-07-04
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/contest/141/problem/E kinda bipartite MST
 * @approach: Observation.
 * @explanation: https://codeforces.com/blog/entry/3571#:~:text=In%20this%20problem,with%20Kruskal%27s%20algorithm.
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

struct edges{
    int u,v;
    char color;
    bool in;
    edges() : in(false) {}
};

// Disjoint Set Union
struct DSU {
    // parent of each node, rank & size of connected components.
    vector<int> par, rnk, sz;
    int c, mx = 1;

    // Initialize DSU -  Every node is parent of itself.
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i=1;i<=n;++i)
            par[i] = i;
    }

    // Find parent of a node...
    int find(int i) {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }

    // If two node belongs to same set
    bool same(int i, int j) {
        return find(i) == find(j);
    }

    // return size of connected components that belongs with node i
    int get_size(int i) {
        return sz[find(i)];
    }

    // count of connected components & size of maximum Connected Component. 
    pair<int,int> cc_count() {
        return {c, mx};
    }

    // merge two components.
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return -1;
        else --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        mx = max(mx, sz[j]);
        if (rnk[i] == rnk[j]) rnk[j]++;
        return j;
    }
};



void solve(){

    int n,m; cin >> n >> m;
    if(n%2 == 0){
        cout << -1 << endl;
        return;
    }
    int need = (n - 1) / 2;
    DSU Blue(n), Red(n);
    int r = 0, b = 0;
    vector<edges>e(m);
    for(int i=0;i<m;i++){
        cin >> e[i].u >> e[i].v >> e[i].color;
        e[i].color = (e[i].color == 'S' ? 'R' : 'B');
        if(e[i].color == 'B') continue;
        if(Red.same(e[i].u, e[i].v)) continue;
        Red.merge(e[i].u, e[i].v);
    }

    for(int i=0;i<m;i++){
        if(e[i].color == 'R') continue;
        if(Red.same(e[i].u, e[i].v)) continue;
        b++;
        Red.merge(e[i].u, e[i].v);
        Blue.merge(e[i].u, e[i].v);
        e[i].in = true;
    }

    for(int i=0;i<m;i++){
        if(b == need) break;
        if(e[i].color == 'R') continue;
        if(Blue.same(e[i].u, e[i].v)) continue;
        b++;
        Blue.merge(e[i].u, e[i].v);
        e[i].in = true;
    }

    if(b != need){
        cout << -1 << endl;
        return;
    }

    for(int i=0;i<m;i++){
        if(r == need) break;
        if(e[i].color == 'B') continue;
        if(Blue.same(e[i].u, e[i].v)) continue;
        r++;
        Blue.merge(e[i].u, e[i].v);
        e[i].in = true;
    }

    if(r != need){
        cout << -1 << endl;
        return;
    }

    cout << n - 1 << endl;
    for(int i=0;i<m;i++){
        if(e[i].in){
            cout << i + 1 << " ";
        }
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