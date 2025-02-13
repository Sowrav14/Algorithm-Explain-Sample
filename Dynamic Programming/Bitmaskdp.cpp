/**
 * @file Bitmaskdp.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-28
 * @copyright Copyright (c) 2024
 * @topic: Bitmask Dp
 * @resource: 
 *          - https://usaco.guide/gold/dp-bitmasks?lang=cpp
 *          - https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/tutorial/
 * @problems:
 *          - https://cses.fi/problemset/task/1690
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 20;
const int M = 1e9 + 7;
const int inf = 1e12;

/*
    dp[s][i] = number of routes that visit all the cities in the subset S
    and end at city i.

    so dp[s][i] = sum of dp[s-{i}][x] where x in {s} and x in adj[i].
 */

vector<int>g[N];
int dp[1<<N][N];

void solve(){

    int n, m; cin >> n >> m;
    for(int i=0;i<m;i++){
        int u, v; cin >> u >> v;
        u--; v--;
        g[v].push_back(u);
    }
    // for first city there is one way. // base case
    dp[1][0] = 1;
    // for all other city
    for(int s=2;s<(1<<n);s++){
        // the routes should contain first city
        if((s & (1 << 0)) == 0) continue;
        // if s contains last city it must contain all city
        if((s & (1 << (n-1))) == 1 and s != ((1 << n) - 1)) continue;

        // now for each city exclude it 
        for(int i=0;i<n;i++){
            // in ?
            if((s & (1 << i)) == 0) continue;
            int prev = s - (1 << i); // excluded
            // now go to each adjacent x
            for(auto x : g[i]){
                if(s & (1 << x)){   // if x is in s
                    dp[s][i] += dp[prev][x];
                    dp[s][i] %= M;
                }
            }
        }
    }
    cout << dp[(1<<n)-1][n-1] << endl;

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