#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

/*                              Frog-3
    dp[i] = min(dp[i], dp[j] + (h[i] - h[j])^2 + C) for all j < i
    here, 
        = dp[j] + (h[i] - h[j])^2 + C
        = dp[j] + h[i]^2 - 2*h[i]*h[j] + h[j]^2 + C
        = -2*h[j]*h[i] + h[j]^2 + dp[j] + h[i]^2 + C
        = m * h[j] + c  where m = -2*h[i], c = h[j]^2 + dp[j], const = h[i]^2 + C

    So, we can apply convex hull trick here.
    height h[i] is working as slope which is increasing.
    therfore -h[i] is decreasing slope. 
    and query will be for minimum value.
*/

struct CHT{
    vector<int> m, c;
    int ptr = 0;

    bool bad(int l1, int l2, int l3){
        // if slope decreasing and query will be minimum or - frog-3
        // if slope increasing and query will be maximum
        return 1.0 * (c[l3] - c[l1]) * (m[l1] - m[l2]) <= 1.0 * (c[l2] - c[l1]) * (m[l1] - m[l3]);

        // if slope decreasing and query will be maximum or
        // if slope increasing and query will be minimum
        // return 1.0 * (c[l3] - c[l1]) * (m[l1] - m[l2]) >= 1.0 * (c[l2] - c[l1]) * (m[l1] - m[l3]);
    }
    // add new line with slope m and constant c
    void add(int _m, int _c){
        m.push_back(_m);
        c.push_back(_c);
        int sz = m.size();
        while(sz >= 3 and bad(sz-3, sz-2, sz-1)){
            m.erase(m.end()-2);
            c.erase(c.end()-2);
            sz--;
        }
    }
    int val(int i, int x) { return m[i] * x + c[i]; }
    //(slope dec+query min), (slope inc+query max) -> x increasing
    //(slope dec+query max), (slope inc+query min) -> x decreasing
    // linear query...
    int query(int x){
        if(ptr >= m.size()) ptr = m.size()-1;
        while(ptr < m.size()-1 and m[ptr+1]*x + c[ptr+1] < m[ptr]*x + c[ptr]) ptr++;
        return m[ptr]*x + c[ptr];
    }
    // query using ternary search
    int bs(int l, int r, int x) {
        int mid = (l + r) / 2;
        if(mid + 1 < m.size() && val(mid + 1, x) < val(mid, x)) return bs(mid + 1, r, x); // > for max
        if(mid - 1 >= 0 && val(mid - 1, x) < val(mid, x)) return bs(l, mid - 1, x); // > for max
        return val(mid, x);
    }
} cht;

void solve(){

    int n, c; cin >> n >> c;
    vector<int> h(n+1), dp(n+1, 0);
    for(int i=1;i<=n;i++) cin >> h[i];

    dp[1] = 0;
    cht.add(-2*h[1], h[1]*h[1]+dp[1]);

    for(int i=2;i<=n;i++){
        dp[i] = cht.bs(0, cht.m.size()-1, h[i]) + h[i]*h[i] + c;
        cht.add(-2*h[i], h[i]*h[i]+dp[i]);
    }
    cout << dp[n] << endl;

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