/**
 * @file Digitdp.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-28
 * @copyright Copyright (c) 2024
 * @topic: Digit Dp Optimized
 * @resources: 
 *          - https://codeforces.com/blog/entry/53960
 *          - https://codeforces.com/blog/entry/95488
 * @problem:
 *          - https://toph.co/p/noora-number
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

int dp[20][1<<10];
int n;
vector<int>num;

// leftmost is the lsb and rightmost is msb
void makeDigit(int a){
    num.clear();
    n = a;
    while(a > 0){
        num.push_back(a % 10);
        a /= 10;
    }   // no reverse!!!
}

int recur(int i, bool f, int mask){
    if(i == -1){
        int cnt = __builtin_popcount(mask);
        int righmost = 31 - __builtin_clz(mask);
        if(cnt == righmost){
            return 1;
        } else {
            return 0;
        }
    }
    if(dp[i][mask] != -1 && f) return dp[i][mask]; // see the f!!!
    int ans = 0;
    int limit;
    if(f) limit = 9;
    else limit = num[i];

    for(int it=0;it<=limit;it++){
        bool nf = f;
        if(it < num[i]) nf = 1;
        int nmask;
        if(it == 0 and mask == 0) nmask = mask;
        else  nmask = mask | (1 << it);
        ans += recur(i-1, nf, nmask);
    }
    return (f ? dp[i][mask] = ans : ans);
}



void solve(){

    int n; cin >> n;
    makeDigit(n);
    cout << recur(num.size()-1, 0, 0) - 1 << endl;

}


signed main(){
    Fast_IO()
    memset(dp, -1, sizeof(dp)); // once...
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << i << ": ";
        solve();
    }
}