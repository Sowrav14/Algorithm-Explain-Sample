#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;

struct articulationPoint{
    int n, Time = 0;
    vector<vector<int>> adj;
    vector<int> ap, disc, low;
    vector<int> aps;
    articulationPoint(){}
    // constructor - construct everything...
    articulationPoint(vector<vector<int>> g, int n) : adj(g), n(n), ap(n+10), disc(n+10), low(n+10){
        Time = 0;
        for (int u = 1; u <= n; u++){
            if (!disc[u]) ap[u] = dfsAP(u, u) > 1; // condition #2
        }
        for(int u = 1; u <= n; u++){
            if(ap[u] == 1) aps.push_back(u);
        }
    }

    int dfsAP(int u, int p) {
        int children = 0;
        low[u] = disc[u] = ++Time;
        for (int& v : adj[u]) {
            if (v == p) continue;                   // we don't want to go back through the same path.
                                                    // if we go back is because we found another way back
            if (!disc[v]) {                         // if V has not been discovered before
                children++;
                dfsAP(v, u);                        // recursive DFS call
                if (disc[u] <= low[v]){             // condition #1
                    ap[u] = 1;
                }
                low[u] = min(low[u], low[v]);       // low[v] might be an ancestor of u
            } else {                                // if v was already discovered means that we found an ancestor
                low[u] = min(low[u], disc[v]);      // finds the ancestor with the least discovery time
            }
        }
        return children;
    }
};

struct articulationBridge{
    int n, Time = 0;
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<pair<int, int>> br;
    articulationBridge(){}
    // constructor - construct everything...
    articulationBridge(vector<vector<int>> &g, int n) : adj(g), n(n), disc(n+10), low(n+10){
        Time = 0;
        for (int u = 1; u <= n; u++) {
            if (!disc[u]) dfsBR(u, 0);
        }
    }

    int dfsBR(int u, int p) {
        low[u] = disc[u] = ++Time;
        for (int& v : adj[u]) {
            if (v == p) continue;                   // we don't want to go back through the same path.
                                                    // if we go back is because we found another way back
            if (!disc[v]) {                         // if V has not been discovered before
                dfsBR(v, u);                        // recursive DFS call
                if (disc[u] < low[v]){              // condition to find a bridge
                    br.push_back({u, v});
                }
                low[u] = min(low[u], low[v]);       // low[v] might be an ancestor of u
            } else {                                // if v was already discovered means that we found an ancestor
                low[u] = min(low[u], disc[v]);      // finds the ancestor with the least discovery time
            }
        }
    }
};



void solve(){

    int n,m; cin >> n >> m;
    vector<vector<int>> g(n+10);
    for(int i=0;i<m;i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    articulationBridge ap(g, n);
    if(ap.br.size() == 0){
        cout << "Sin bloqueos" << endl;
        return;
    }
    sort(ap.br.begin(), ap.br.end());
    cout << ap.br.size() << endl;
    for(auto i : ap.br){
        cout << i.first << " " << i.second << endl;
    }

}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Caso #" << i << endl;
        solve();
    }
}