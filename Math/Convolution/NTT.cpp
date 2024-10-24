/**
 * @file NTT.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-10-24
 * @copyright Copyright (c) 2024
 * @topic: Number theoretic transform
 * @resources:
 *            - https://cp-algorithms.com/algebra/fft.html#number-theoretic-transform:~:text=and%20their%20powers.-,Number%20theoretic%20transform,-%C2%B6
 *            - https://codeforces.com/blog/entry/48798#:~:text=NTT%20(Number%20Theoretic%20Transform)
 * @problems:
 *          - https://vjudge.net/problem/Yosupo-convolution_mod
 *          -               
 */
#include<bits/stdc++.h>
using namespace std;

#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const int N = 1 << 20;
const int mod = 998244353;
const int root = 3;

int lim, rev[N], w[N], wn[N], inv_lim;

void reduce(int &x) { x = (x + mod) % mod; }

/*  Calculate a^b % mod  */
int POW(int x, int y, int ans = 1) {
    while(y){
        if (y & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

void precompute(int len) {
    lim = wn[0] = 1; int s = -1;
    while (lim < len) lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = POW(root, (mod - 1) / lim);
    inv_lim = POW(lim, mod - 2);
    for (int i = 1; i < lim; ++i) wn[i] = (wn[i - 1] * g) % mod;
}

void ntt(vector<int> &a, int typ) {
    for(int i = 0; i < lim; ++i) if(i < rev[i]) swap(a[i], a[rev[i]]);
    for(int i = 1; i < lim; i <<= 1){
        for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1){
            for (int k = 0; k < i; ++k){
                const int x = a[k + j], y = a[k + j + i] * w[k] % mod;
                reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
            }
        }
    }
    if (!typ) {
        reverse(a.begin() + 1, a.begin() + lim);
        for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * inv_lim % mod;
    }
}

vector<int> multiply(vector<int> &f, vector<int> &g) {
    if (f.empty() or g.empty()) return {};
    int n = (int)f.size() + (int)g.size() - 1;
    if (n == 1) return {(int)((long long) f[0] * g[0] % mod)};
    precompute(n);
    vector<int> a = f, b = g;
    a.resize(lim); b.resize(lim);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * b[i] % mod;
    ntt(a, 0);
    a.resize(n + 1);
    return a;
}

void solve(){

    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    auto ans = multiply(a, b);
    ans.resize(n + m - 1);
    for (auto x: ans) cout << x << ' '; cout << '\n';

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