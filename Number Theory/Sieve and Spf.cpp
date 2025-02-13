#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;


vector<int> primes;
bool is_prime[N]; 

// use bitset<N> is_prime; to have O(N/64) memory complexity
// using bitset you can solve upto around N = 10^8 in 1s
void sieve_v0() {
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i < N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

// sieve with smallest prime factors (spf)
int spf[N];
void sieve() {
    for (int i = 2; i < N; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (spf[i] == i) {
            primes.push_back(i);
        }
    }
}


void solve(){

    // dont forget to call sieve from main function....
    sieve();
    cout << spf[9] << endl;

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