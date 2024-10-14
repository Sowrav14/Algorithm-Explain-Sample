/**
 * @file Heavy Light Decomposition.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-10-14
 * @copyright Copyright (c) 2024
 * @problem: cses -> https://www.hackerrank.com/challenges/subtrees-and-paths/problem
 * @approach: Heavy Light Decomposition (HLD)
 * @explanation: https://cp-algorithms.com/graph/hld.html
 * @see_also: 
 *              - https://cses.fi/problemset/task/2134
 *              - https://cses.fi/problemset/task/1138
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;
const int LG = 18;


/* Segment Tree for Euler Tour Technique */

struct ST {
#define lc (n << 1)
#define rc ((n << 1) | 1)
    
    int val[N];
    int t[4 * N], lazy[4 * N];
    
    ST() {
        fill(t, t + 4 * N, -inf);
        fill(lazy, lazy + 4 * N, 0);
    }

    inline void push(int n, int b, int e) {
        if(lazy[n] == 0) return;
        t[n] = t[n] + lazy[n];
        if(b != e) {
            lazy[lc] = lazy[lc] + lazy[n];
            lazy[rc] = lazy[rc] + lazy[n];
        }
        lazy[n] = 0;
    }

    inline int combine(int a, int b) {
        return max(a, b); //merge left and right queries
    }

    inline void pull(int n) {
        t[n] = max(t[lc], t[rc]); //merge lower nodes of the tree to get the parent node
    }

    void build(int n, int b, int e) {
        if(b == e) {
            t[n] = val[b];
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }

    void upd(int n, int b, int e, int i, int j, int v) {
        push(n, b, e);
        if(j < b || e < i) return;
        if(i <= b && e <= j) {
            lazy[n] += v;
            push(n, b, e);
            return;
        }
        int mid = (b + e) >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        pull(n);
    }

    int query(int n, int b, int e, int i, int j) {
        push(n, b, e);
        if(i > e || b > j) return -inf;
        if(i <= b && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
} t;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];

/* Dfs to configure LCA */
void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    if(p) g[u].erase(find(g[u].begin(), g[u].end(), p)); // making uni-directional
    for (auto &v : g[u]){
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]); // 0 th node is heavy
        }
    }

}

/* Return least common ancestor of u and v */
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

/* Return kth node from u */
int kth(int u, int k) {
    assert(k >= 0);
    for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
    return u;
}

/* Heavy Light Decomposition */
/* Eular tour technique for segment tree */

int T, head[N], st[N], en[N];
void dfs_hld(int u) {
    st[u] = ++T;
    for (auto v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v); // decomposing path
        dfs_hld(v);
    }
    en[u] = T;
}

int n;

/* Return the required answer for path v->l where l is ancestor of v */
int query_up(int u, int v) {
    int ans = -inf;
    while(head[u] != head[v]) {
        ans = max(ans, t.query(1, 1, n, st[head[u]], st[u]));
        u = par[head[u]][0];
    }
    ans = max(ans, t.query(1, 1, n, st[v], st[u]));
    return ans;
}

/* Return the required answer for path u->v */
int query(int u, int v) {
    int l = lca(u, v);
    int ans = query_up(u, l);
    if (v != l) ans = max(ans, query_up(v, kth(v, dep[v] - dep[l] - 1)));
    return ans;
}



void solve(){

    cin >> n;
    for(int i=1;i<n;i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    head[1] = 1;
    dfs_hld(1);
    t.build(1, 1, n);

	int q; cin >> q;
    while (q--) {
        string ty; cin >> ty;
        int u, v; cin >> u >> v;
        if (ty == "add") {
            t.upd(1, 1, n, st[u], en[u], v);
        } else {
            cout << query(u, v) << '\n';
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