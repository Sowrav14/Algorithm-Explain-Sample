#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

vector<int>g[N];
int c[N];
int ans[N];

struct Node{
    map<int,int>freq;
    int mx = 0;
    int sum = 0;
};

Node& merge(Node a, Node &b){
    if(a.freq.size() > b.freq.size()) swap(a, b);

    for(auto &i : a.freq){
        b.freq[i.first] += i.second;
        if(b.freq[i.first] > b.mx){
            b.mx = b.freq[i.first];
            b.sum = i.first;
        } else if(b.freq[i.first] == b.mx){
            b.sum += i.first;
        }
    }
    return b;
}

Node dfs(int u, int p){
    
    Node x;
    int color = c[u];
    x.freq[color]++;
    x.mx = 1;
    x.sum = color;
    
    for(auto v : g[u]){
        if(v == p) continue;
        x = merge(dfs(v, u), x);
    }
    
    ans[u] = x.sum;
    return x;
}

void solve(){

    int n; cin >> n;
    for(int i=1;i<=n;i++){
        cin >> c[i];
    }

    for(int i=1;i<n;i++){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    for(int i=1;i<=n;i++) cout << ans[i] << " \n"[i==n];

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