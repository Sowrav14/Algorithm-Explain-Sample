#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int inf = 1e12;
vector<pair<int,int>>g[N];
vector<int>dist(N, inf);


void bfs(int s){
    deque<int>q;
    q.push_back(s);
    dist[s] = 0;

    while(!q.empty()){
        int v = q.front();
        q.pop_front();

        for(auto child : g[v]){
            int u = child.first;
            int w = child.second;

            if(dist[v] + w < dist[u]){
                dist[u] = dist[v] + w;
                if(w == 1){
                    q.push_back(u);
                } else {
                    q.push_front(v);
                }
            }
        }
    }
}


void solve(){

    int n,m; cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v; cin >> u >> v;
        g[u].push_back({v, 0});
        g[v].push_back({u, 1});
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