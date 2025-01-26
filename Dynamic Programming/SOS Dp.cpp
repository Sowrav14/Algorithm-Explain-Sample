#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;
const int B = 21;

int a[1<<B];
int dpor[1<<B], dpand[1<<B];

void subset(){
    for(int i=0;i<B;i++){
        for(int mask=0;mask<(1<<B);mask++){
            if((mask & (1<<i)) != 0){
                dpor[mask] += dpor[mask^(1<<i)];
            }
        }
    }
}

void superset(){
    for(int i=0;i<B;i++){
        for(int mask=(1<<B)-1;mask>=0;mask--){
            if((mask & (1<<i)) == 0){
                dpand[mask] += dpand[mask^(1<<i)];
            }
        }
    }
}

void solve(){

    int n; cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        dpor[a[i]]++;
        dpand[a[i]]++;
    }

    // x | y = x means y is subset of x
    subset();
    // x & y = x means y is superset of x
    superset();

    // x&y!=0 means x and y have common element
    // which means y can not be subset of complement of x

    for(int i=1;i<=n;i++){
        cout << dpor[a[i]] << " " << dpand[a[i]] << " " << (n - dpor[(1<<B)-1-a[i]]) << endl;
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