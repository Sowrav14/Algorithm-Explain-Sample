/**
 * @file Multiset Hashing.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-08
 * @copyright Copyright (c) 2024
 * @topic: Multiset hashing
 * @problem: -https://atcoder.jp/contests/abc367/tasks/abc367_f
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
const int P1 = 1e9 + 7, P2 = 127657753;
const int inf = 1e12;
const int M1 = 1e9 + 9, M2 = 987654319;

int n, q;
int a[N], b[N];

int hashA1[N], hashB1[N];
int hashA2[N], hashB2[N];

// Big Mod
int A_pow_B(int a,int b, int mod){
    int ret = 1;
    while(b){
        if(b&1) {
            ret = (1ll * ret%mod * a%mod) % mod;
        }
        a = (1ll * a%mod * a%mod) % mod;
        b >>= 1;
    }
    return ret;
}



void solve(){

    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];

    for(int i=1;i<=n;i++){
        hashA1[i] = (hashA1[i-1]%M1 + A_pow_B(a[i]+P1, P1, M1)%M1)%M1;
        hashA2[i] = (hashA2[i-1]%M2 + A_pow_B(a[i]+P2, P2, M2)%M2)%M2;
        hashB1[i] = (hashB1[i-1]%M1 + A_pow_B(b[i]+P1, P1, M1)%M1)%M1;
        hashB2[i] = (hashB2[i-1]%M2 + A_pow_B(b[i]+P2, P2, M2)%M2)%M2;
    }

    while(q--){
        int l, r, L, R; cin >> l >> r >> L >> R;
        int hasha1 = (hashA1[r]%M1 - hashA1[l-1]%M1 + M1)%M1;
        int hashb1 = (hashB1[R]%M1 - hashB1[L-1]%M1 + M1)%M1;
        int hasha2 = (hashA2[r]%M2 - hashA2[l-1]%M2 + M2)%M2;
        int hashb2 = (hashB2[R]%M2 - hashB2[L-1]%M2 + M2)%M2;

        if(hasha1 == hashb1 and hasha2 == hashb2){
            cout << "Yes" << endl;
        } else{
            cout << "No" << endl;
        }
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