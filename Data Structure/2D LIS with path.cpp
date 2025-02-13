/**
 * @file F_Gather_Coins.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2025-01-02
 * @copyright Copyright (c) 2025
 * @topic: LIS
 * @tag: 2D_LIS LIS_Path print LIS
 * @problem:https://atcoder.jp/contests/abc369/tasks/abc369_f?lang=en
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;


void solve(){

    int h, w, n; cin >> h >> w >> n;
    vector<pair<int,int>>coins;
    for(int i=0;i<n;i++){
        int x, y; cin >> x >> y;
        coins.push_back({x, y});
    }
    sort(coins.begin(), coins.end());
    // vector for trace LIS Length
    vector<int>d(n, 1e9);
    // vector for trace elements present in lis
    vector<int>id(n, -1); // -1 means lis didn't grow here yet
    // vector for trace ordering in elements of lis
    vector<int>pre(n, -1);

    for(int i=0;i<n;i++){
        int x = coins[i].second;
        // find suitable position of this element and update vectors.
        int j = upper_bound(d.begin(), d.end(), x) - d.begin();
        d[j] = x;
        id[j] = i; // i'th element is now on j'th length of lis.
        pre[i] = j ? id[j-1] : -1;  // whom it will follow.
    }

    int m = n - 1;
    while(id[m] == -1) m--;
    // now lis lenght is in m+1 (0 - m);
    // cout << m << endl;

    // no get the Lis.
    vector<pair<int,int>>path{{h, w}};
    int cur = id[m];
    while(cur != -1){
        path.push_back(coins[cur]);
        cur = pre[cur];
    }
    path.push_back({1, 1});

    // got the lis??
    reverse(path.begin(), path.end());
    // cout << path.size() << endl;

    string ans = "";
    for(int i=0;i<path.size()-1;i++){
        int d = path[i+1].first - path[i].first;
        int r = path[i+1].second - path[i].second;
        while(d--) ans += "D";
        while(r--) ans += "R";
    }

    cout << m + 1 << endl;
    cout << ans << endl;

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