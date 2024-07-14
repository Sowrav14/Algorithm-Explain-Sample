/*
 * @file Smaller Element.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-07-04
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/problemset/problem/817/D
 * @approach: Next Greater / Smaller element calculation...
 * @explanation: https://codeforces.com/blog/entry/52638
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
int n;
vector<int>a;

// calculate index of nearest smaller element in left & right for each i in n of array a.
void nearest_smaller(int n, vector<int>&a, vector<int>&left, vector<int>&right){
    
    left.resize(n+1, 0), right.resize(n+1, n+1);
    stack<pair<int,int>>st;
    
    // calculating the nearest smaller element in the left...
    st.push({-1e18, 0});
    for(int i=1;i<=n;i++){
        while(st.top().first > a[i]){   // check this !!!
            st.pop();
        }
        left[i] = st.top().second;
        st.push({a[i], i});
    }

    while(!st.empty()) st.pop();

    // calculating the nearest smaller element in the right...
    st.push({-1e18, n+1});
    for(int i=n;i>=1;i--){
        while(st.top().first >= a[i]){   // check this !!!
            st.pop();
        }
        right[i] = st.top().second;
        st.push({a[i], i});
    }

    // got this in left and right vector...
    // for(int i=1;i<=n;i++){
    //     cout << left[i] << " " << right[i] << endl;
    // }
}

int calculate(vector<int>&a, int n){
    vector<int>left, right;
    nearest_smaller(n, a, left, right);

    int ans = 0;
    for(int i=1;i<=n;i++){
        int l = left[i];
        int r = right[i];

        ans += a[i] * (i - l) * (r - i);
    }
    return ans;
}


void solve(){

    cin >> n;
    a.resize(n+1, 0);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }

    int ans = calculate(a, n);
    for(int i=1;i<=n;i++) a[i] = -a[i];
    ans += calculate(a, n);
    cout << abs(ans) << endl;

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