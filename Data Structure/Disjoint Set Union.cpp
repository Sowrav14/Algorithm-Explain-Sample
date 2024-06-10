#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    DSU dsu = DSU(n);
    int mx_size = 1;

    for(int i=1;i<=m;i++){
        int u,v; cin >> u >> v;
        dsu.merge(u, v);
        cout << dsu.cc_count().first << " " << dsu.cc_count().second << endl;
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