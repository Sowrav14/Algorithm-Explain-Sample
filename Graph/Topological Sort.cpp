#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const int N = 1e5 + 9;
vector<int> g[N];
bool vis[N];
vector<int> ord;


void dfs(int u){
    vis[u] = true;
    for(auto v:g[u]){
        if(!vis[v]){
            dfs(v);
        }
    }
    ord.push_back(u);
}

void reset(int n){
    ord.clear();
    for(int i=1;i<=n;i++){
        vis[i] = 0;
        g[i].clear();
    }
}


void solve(){

    int n,m; cin >> n >> m;
    while(m--){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i);
        }
    }

    reverse(ord.begin(), ord.end());

    // check if valid
    vector<int>pos(n+1);
    for(int i=0;i<ord.size();i++){
        pos[ord[i]] = i;
    }

    for(int u=1;u<=n;u++){
        for(auto v : g[u]){
            if(pos[u] > pos[v]){
                cout << "IMPOSSIBLE" << endl;
                return;
            }
        }
    }


    for(auto u : ord) cout << u << " "; cout << endl;

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