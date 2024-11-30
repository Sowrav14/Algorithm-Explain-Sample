/**
 * @file Digitdp.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-28
 * @copyright Copyright (c) 2024
 * @topic: Digit Dp
 * @resources: 
 *          - https://codeforces.com/blog/entry/53960
 *          - https://codeforces.com/blog/entry/95488
 * @problem:
 *          - https://lightoj.com/problem/investigation
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

int dp[20][2][100][100];
struct Digitdp{
    int n, mod;
    vector<int>num;

    Digitdp(int a, int k){
        n = a;
        mod = k > 100 ? 100 : k;
        while(a > 0){
            num.push_back(a % 10);
            a /= 10;
        }
        reverse(num.begin(), num.end());
    }

    int recur(int i, bool f, int dsum, int sum){
        if(i == num.size()){
            if(sum == 0 and dsum == 0){
                return 1;
            } else {
                return 0;
            }
        }
        if(dp[i][f][dsum][sum] != -1) return dp[i][f][dsum][sum];
        int ans = 0;
        int limit;
        if(f) limit = 9;
        else limit = num[i];

        for(int it=0;it<=limit;it++){
            bool nf = f;
            if(it < num[i]) nf = 1;
            ans += recur(i+1, nf, (dsum + it)%mod, (sum*10+it)%mod);
        }
        return dp[i][f][dsum][sum] = ans;
    }

    int query(){
        if(mod > 90) return 0;
        memset(dp, -1, sizeof(dp));
        return recur(0, 0, 0, 0);
    }
};


void solve(){

    int a, b, k; cin >> a >> b >> k;
    Digitdp dp1(a-1, k), dp2(b, k);
    cout << dp2.query() - dp1.query() << endl;

}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case " << i << ": ";
        solve();
    }
}