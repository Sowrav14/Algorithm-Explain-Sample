#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

// Logarithmic approach.
int logdigit(int n) {
    // factorial exists only for n>=0
    if (n < 0) return 0;
 
    // base case
    if (n <= 1) return 1;
 
    // else iterate through n and calculate the
    // value
    double digits = 0;
    for (int i = 2; i <= n; i++)
        digits += log10(i);
 
    return floor(digits) + 1;
}

// stirling approach (#include<cmath> is required)
int stirlingdigit(int n) {
    if (n < 0) return 0;
    if (n < 2) return 1;
    double x = (n * log10(n / M_E) + log10(2 * M_PI * n) / 2.0);
    return floor(x) + 1;
}



void solve(){

    int x; cin >> x;
    cout << logdigit(x) << " ";
    cout << stirlingdigit(x) << endl;

}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}