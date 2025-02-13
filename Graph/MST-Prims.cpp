#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define pii pair<int,int>
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
vector<pii>g[N];
int vis[N];


int Prims(int root){
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    // priority_queue will contain <weight, adjacent_node>
    // push root as initial node with weight = 0.
    pq.push({0, root});
    int mst = 0;
    while(!pq.empty()){
        // extract adjacent node with minimum edge_weight.
        int w = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        // if adjacent node is already visited then discard the edge.
        if(vis[v]){
            continue;
        }

        // add this edge to mst and add all of its edges to priority queue
        mst += w;
        vis[v] = true;
        for(auto u : g[v]){
            if(!vis[u.second]){
                pq.push(u);
            }
        }
    }

    return mst;
}


void solve(){
        
    int n,m; cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    cout << Prims(1) << endl;
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