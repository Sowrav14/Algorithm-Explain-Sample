/*
 * @file Bellman Ford.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-19
 * @copyright Copyright (c) 2024
 * @problem: CSES -> https://cses.fi/problemset/submit/1197/
 * @approach: Bellman Ford algorithm for single source shortest path && detect negative cycle 
 * @explanation:
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3e5 + 9;
const int inf = 2e9;
struct st {
    int a, b, cost;
} e[N];

void solve(){

    int n,m; cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> e[i].a >> e[i].b >> e[i].cost;
    }

    vector<int> d(n+10, inf);
    int s = 1; d[s] = 0; // any source...
    vector<int> p(n+10, -1);
    int last_updated;
    for(int i=0;i<n;i++){
        last_updated = -1;
        for(int j=0;j<m;j++){
            // think here....
            /* if(d[e[j].a] < inf){
                if(d[e[j].b] > d[e[j].a] + e[j].cost){
                    d[e[j].b] = max(-inf, d[e[j].a] + e[j].cost);
                    p[e[j].b] = e[j].a;
                    last_updated = e[j].b;
                }
            } */
           if(d[e[j].b] > d[e[j].a] + e[j].cost){
                d[e[j].b] = d[e[j].a] + e[j].cost;
                p[e[j].b] = e[j].a;
                last_updated = e[j].b;
            }
        }
    }
    // if in last iteration no node is updated then last_updated will be -1
    if(last_updated == -1){
        cout << "NO" << endl;
        return;
    }

    // last_updated belongs to the negative cycle so print by using it...
    cout << "YES" << endl;
    for (int i=0; i<n; ++i) last_updated = p[last_updated];
    stack<int>path;
    int cur = last_updated;
    while(1){
        path.push(cur);
        if(cur == last_updated and path.size() > 1) break;
        cur = p[cur];
    }
    while(!path.empty()) cout << path.top() << " ", path.pop();

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