/**
 * @file Knuth Optimization.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2025-01-23
 * @copyright Copyright (c) 2025
 * @topic: Knuth Optimization
 * @resources: https://cp-algorithms.com/dynamic_programming/knuth-optimization.html
 * @problems: 
 *          - https://vjudge.net/problem/ZOJ-2860
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1000 + 10;
const int M = 1e9 + 7;
const int inf = 1e18;

/*
    Knuths optimization works for optimization over sub arrays
    for which optimal middle point depends monotonously on the end points.
    Let opt[l,r] be the first middle point for (l,r) sub array which gives optimal result.
    It can be proven that opt[l,r-1] <= opt[l,r] <= opt[l+1,r]
    this means monotonicity of mid by l and r.
    Applying this optimization reduces time complexity from O(k^3) to O(k^2)
    because with fixed s (sub array length) we have m_right(l) = opt[l+1][r] = m_left(l+1).
    That's why nested l and m loops require not more than 2k iterations overall.
*/

int n, k;
int a[N], opt[N][N];
int dp[N][N];

void knuthOptimize(){

    // generate all length subarray...
    for(int s=0;s<=k;s++){
        // generate all [l, r]
        for(int l=0;l+s<=k;l++){
            int r = l + s;
            // base case
            if(s < 2){
                dp[l][r] = 0;
                opt[l][r] = l;
                continue;
            }

            int optl = opt[l][r-1];
            int optr = opt[l+1][r];
            dp[l][r] = inf;
            for(int op=optl;op<=optr;op++){
                int cur = dp[l][op] + dp[op][r] + (a[r] - a[l]);
                if(dp[l][r] > cur){
                    dp[l][r] = cur;
                    opt[l][r] = op;
                }
            }
        }
    }
    
    cout << dp[0][k] << endl;
}


void solve(){

    while(cin >> n >> k){
        for(int i=1;i<=k;i++) cin >> a[i];
        a[0] = 0;
        a[k+1] = n;
        k++;
        knuthOptimize();
    }

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