/**
 * @file Divide and Conquer Trick.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2025-01-08
 * @copyright Copyright (c) 2025
 * @topic: Divide and Conquer Trick in Dynamic Programming
 * @resources: 
 *          - https://youkn0wwho.academy/topic-list/divide_and_conquer_optimization
 *          - https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
 * @problem: https://cses.fi/problemset/task/2086
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3000 + 10;
const int M = 1e9 + 7;
const int inf = 1e18;

int n, k;
int a[N];
int cost[N][N];
int dp[N][N];

// this also can be done with prefix sum in 1D.
void calc_cost(){
    for(int i=1;i<=n;i++){
        cost[i][i] = a[i];
        for(int j=i+1;j<=n;j++){
            cost[i][j] = cost[i][j-1] + a[j];
        }
        // for(int j=i;j<=n;j++) cout << cost[i][j] << " \n"[j == n];
    }
}

// for ith cut. possible region is [l...r] and feasible region is [optl...optr]
void divide_conquer_dp(int i, int l, int r, int optl, int optr){
    if(l>r) return;
    // let't try for the first half
    pair<int,int> opt = {inf, l};
    int m = (l + r) / 2;
    for(int j=optl;j<min(m, optr+1);j++){
        // assume cut point is j so the cost added will be cost[j+1...m]
        opt = min(opt, {dp[i-1][j] + cost[j+1][m] * cost[j+1][m], j});
    }
    dp[i][m] = opt.first;
    // cout << i << " " << m << " " << opt.second << " " << dp[i][m] << endl; // explain everyting!!
    
    // for [l...m-1] region feasible region will be changed accordingly
    divide_conquer_dp(i, l, m-1, optl, opt.second);
    // for [m+1...r] region feasible region will be changed accordingly
    divide_conquer_dp(i, m+1, r, opt.second, optr);
}


void solve(){

    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];

    calc_cost();
    for (int j=0;j<=n;j++) dp[0][j] = inf;
    dp[0][0] = 0;

    for(int i=1;i<=k;i++) divide_conquer_dp(i, 1, n, 0, n-1);
    cout << dp[k][n] << endl;

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