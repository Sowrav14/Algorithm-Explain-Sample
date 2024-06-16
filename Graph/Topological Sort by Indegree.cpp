#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

vector<set<int>> g;
set<int> to_remove;
vector<int>in;


void reset(int n){
    g.resize(n + 10);
    in.resize(n+10);
    to_remove.clear();
    for(int i=1;i<=n;i++){
        g[i].clear();
        in[i] = i - 1;
    }
}


void solve(){

    int n,m; cin >> n >> m;
    reset(n);
    for(int i=0;i<m;i++){
        int u, v; cin >> u >> v;
        g[u].insert(v);
        in[v]--;
    }
    stack<int>topo;
    vector<int>topological_order;
    for(int i=1;i<=n;i++){
        to_remove.insert(i);
        if(in[i] == 0) topo.push(i);
    }

    while(!topo.empty()){
        int u = topo.top();
        topo.pop();
        topological_order.push_back(u);
        cout << u << " ";
        to_remove.erase(u);

        stack<int>adj;
        for(auto v : to_remove){
            if(!g[u].count(v) and v > u){
                adj.push(v);
            }
        }

        while(!adj.empty()){
            int v = adj.top(); adj.pop();
            in[v]--;
            if(in[v] == 0) topo.push(v);
        }
    }

    // for(auto i : topological_order) cout << i << " ";
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