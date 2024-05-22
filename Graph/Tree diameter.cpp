#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
vector<int>g[N];

int farthest(int s, int n, vector<int> &d) {
    static const int inf = N;
    d.assign(n + 1, inf); d[s] = 0;
    vector<bool> vis(n + 1);
    queue<int> q; q.push(s);
    vis[s] = 1; int last = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
        if (vis[v]) continue;
        d[v] = d[u] + 1;
        q.push(v); vis[v] = 1;
        }
        last = u;
    }
    return last;
}


void solve(){

    int n; cin >> n;
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dx, dy;
    // finding distance from 1.
    int x = farthest(1, n, dx);
    // finding distance from x which is fartest from 1.
    int y = farthest(x, n, dx);
    // finding distance from y which is fartest from x.
    // x -> y will be the diameter.
    farthest(y, n, dy);

    for (int i = 1; i <= n; i++) {
        // maximum distance of i'th node...
        cout << max(dx[i], dy[i]) << ' ';
    } cout << endl;

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