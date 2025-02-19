#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

double findNthRoot(double x, int n){
 
    // Initialize boundary values
    double low, high;
    if (x >= 0 and x <= 1){
        low = x;
        high = 1;
    }
    else{
        low = 1;
        high = x;
    }
 
    // Used for taking approximations
    // of the answer
    double epsilon = 0.00000001;
 
    // Do binary search
    double guess = (low + high) / 2;
    while (abs((pow(guess, n)) - x) >= epsilon) {
        if (pow(guess, n) > x){
            high = guess;
        }
        else{
            low = guess;
        }
        guess = (low + high) / 2;
    }
 
    return guess;
}



void solve(){

    double num; cin >> num;
    int n; cin >> n;
    cout << fixed << setprecision(10) << findNthRoot(num, n);

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