/**
 * @file Subsetsum3.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-01
 * @copyright Copyright (c) 2024
 * @problem: https://atcoder.jp/contests/abc267/tasks/abc267_h
 * @solution: https://atcoder.jp/contests/abc267/editorial/4751
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
int POW(int x, int y, int ans = 1) {
  for (; y; y >>= 1, x = (long long) x * x % mod) if (y & 1) ans = (long long) ans * x % mod;
  return ans;
}
void precompute(int len) {
  lim = wn[0] = 1; int s = -1;
  while (lim < len) lim <<= 1, ++s;
  for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
  const int g = POW(root, (mod - 1) / lim);
  inv_lim = POW(lim, mod - 2);
  for (int i = 1; i < lim; ++i) wn[i] = (long long) wn[i - 1] * g % mod;
}
void ntt(vector<int> &a, int typ) {
  for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
    for (int j = 0; j < lim; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        const int x = a[k + j], y = (long long) a[k + j + i] * w[k] % mod;
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
int f[N],invf[N];
// Big Mod
int A_pow_B(int a,int b){
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
// Calculating factorials and inverse factorial
void fact_invfact(){
    f[0] = 1;
    for(int i=1;i<N;i++){
        f[i] = (1ll * f[i-1]%mod * i%mod) % mod;
    }

    // calculate fact inverse
    invf[N-1] = A_pow_B(f[N-1],mod-2);
    for(int i=N-2;i>=0;i--){
        invf[i] = (1ll * invf[i+1]%mod * (i+1)%mod) % mod;
    }
}
// Calculating nCr
int nCr(int n, int r){
    if(n < 0 or n < r) return 0;
    return (1ll * f[n]%mod * invf[n-r]%mod * invf[r]%mod) % mod ; 
}
// Calculating nPr
int nPr(int n, int r){
    if(n < 0 or n < r) return 0;
    return (1ll * f[n]%mod * invf[n-r]%mod) % mod;
}
// dp[i][j] = k means there is k ways to make sum j with i elements.
int dp[2][N];
void solve(){

    int n,k; cin >> n >> k;
		vector<int>cnt(11, 0);
		for(int i=0;i<n;i++){
			int x; cin >> x;
			cnt[x]++;
		}

		dp[0][0] = 1;
		int sum = 0;

		for(int i = 1; i <= 10; i++) {
			if(!cnt[i]) continue;
			int sum1 = sum + cnt[i] * i;
			vector<int> v1(sum + 1), v2(sum + 1);
			vector<int> u1(sum1 + 1), u2(sum1 + 1);
			
			// 
			for(int j = 0; j <= sum; j++) {
				v1[j] = dp[0][j];
				v2[j] = dp[1][j];
			}
			for(int j = 1; j <= cnt[i]; j += 2) {
				int a = 1LL * invf[j] * invf[cnt[i] - j] % mod;
				u1[j * i] = a;
			}
			for(int j = 2; j <= cnt[i]; j += 2) {
				int a = 1LL * invf[j] * invf[cnt[i] - j] % mod;
				u2[j * i] = a;
			}

			auto a1 = multiply(v1, u1); // 1
			auto a2 = multiply(v2, u1); // 0
			auto b1 = multiply(v1, u2); // 0
			auto b2 = multiply(v2, u2); // 1

			for(int j = 0; j <= sum1; j++) {
				dp[0][j] += f[cnt[i]] * a2[j] % mod;
				if(dp[0][j] >= mod) dp[0][j] -= mod;

				dp[0][j] += f[cnt[i]] * b1[j] % mod;
				if(dp[0][j] >= mod) dp[0][j] -= mod;

				dp[1][j] += f[cnt[i]] * a1[j] % mod;
				if(dp[1][j] >= mod) dp[1][j] -= mod;

				dp[1][j] += f[cnt[i]] * b2[j] % mod;
				if(dp[1][j] >= mod) dp[1][j] -= mod;
			}

			sum = sum1;
		}

		cout << dp[1][k] << endl;

}


signed main(){
    Fast_IO();
		fact_invfact();
    int t = 1;
    // cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case #" << i << ": ";
        solve();
    }
}