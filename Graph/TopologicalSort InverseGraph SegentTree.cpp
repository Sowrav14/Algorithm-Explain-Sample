/*
 * @file K_Topological_Sort.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-16
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/gym/101102/problem/K?csrf_token=5cd073f9d7e0c245ef167fc3c048c2a4
 * @approach: Topological sort using Segment tree.
 * @explanation: see code
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int inf = 1e9;
vector<int>g[N];
int tree[4*N], prop[4*N];

// build Range Minimum Segment tree (storing the indegree)
// tree[i] = j means there is  a node with minimum j indegree in this branch
// tree[i] = i - 1 for all i -> (1...n)
void build(int node, int l, int r){
    if(l == r){
        tree[node] = l - 1;
        return;
    }

    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node + 1, mid + 1, r);
    tree[node] = min(tree[2*node], tree[2*node + 1]);
}

void push(int node, int l, int r){
    tree[node] += prop[node];
    if(l != r){
        prop[2 * node] += prop[node];
        prop[2*node+1] += prop[node];
    }
    prop[node] = 0;
}

// Usual update function of Range Minimum Segment tree.
void rangeupdate(int node, int l, int r, int i, int j, int val){
    push(node, l, r);
    if(i<=l and j>=r){
	    prop[node] += val;
        push(node, l, r);
        return;
    }
    if(i>r or j<l) return;

    int mid = (l + r) / 2;
    rangeupdate(2*node, l, mid, i, j, val);
    rangeupdate(2*node+1, mid+1, r, i, j, val);
    tree[node] = min(tree[2*node], tree[2*node+1]);
}


int query(int node, int l, int r, int i, int j, int val = 0){
    push(node, l, r);
    if(i>r or j<l){
        return 0;
    }
    if(i<=l and j>=r){
        return tree[node] + (r - l + 1) * val;
    }

    int mid = (l + r) / 2;
    int left = query(2*node, l, mid, i, j, val+prop[node]);
    int right = query(2*node+1, mid+1, r, i, j, val+prop[node]);
    return min(left, right);
}

// Find the greater node with indegree 0.
int findzero(int node, int l, int r){
    push(node, l, r);
    if(tree[node] > 0) return -1;
    if(l == r) return l;

    int mid = (l + r) / 2;
    int x = findzero(2*node+1, mid+1, r);
    if(x != -1){
        return x;
    }
    return findzero(2*node, l, mid);
}


void solve(){

    int n,m; cin >> n >> m;
    for(int i=1;i<=4*n;i++){
        if(i<=n) g[i].clear();
        tree[i] = prop[i] = 0;
    }

    build(1, 1, n); // Initialize segment tree.
    // initialy indegree of ith node = i - 1;
    // given (u, v) that there is no edge between (u, v)
    // for each (u, v) reduce the indegree of v by 1.
    for(int i=0;i<m;i++){
        int u,v ; cin >> u >> v;
        g[u].push_back(v);
        rangeupdate(1, 1, n, v, v, -1);
    }
    
    // in each iteration find the largest node (u) with indegree 0
    // as it is processed update the indegree of this node to inf.
    // as all node v (v > u) is its adjacent so reduce indegree for all (u+1...n) by 1
    // but as in graph g means there is no edge in (u, v)
    // so increase indegree for all adjacent of (u) by 1 to settle the score.
    for(int i=0;i<n;i++){
        int u = findzero(1, 1, n);
        for(auto v : g[u]){
            rangeupdate(1, 1, n, v, v, 1);
        }

        cout << u << " ";
        rangeupdate(1, 1, n, u, u, inf);
        rangeupdate(1, 1, n, u+1, n, -1);
    }
    cout << endl; 

}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}