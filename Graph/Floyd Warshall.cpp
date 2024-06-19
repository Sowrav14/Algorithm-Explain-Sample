#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1010;
const int inf = 1e15;
int g[N][N];




void Floyd_Warshall(int n){
    for(int k=1;k<=n;++k) {
        for(int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

void solve(){

    int n,m,q; cin >> n >> m >> q;
    // Initialize...
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g[i][j] = (i == j ? 0 : inf);
        }
    }

    for(int i=0;i<m;i++){
        int u,v,w; cin >> u >> v >> w;
        g[u][v] = min(w, g[u][v]);
        g[v][u] = min(w, g[u][v]);
    }

    Floyd_Warshall(n);

    while(q--){
        int u,v; cin >> u >> v;
        cout << (g[u][v] >= inf ? -1 : g[u][v]) << endl;
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