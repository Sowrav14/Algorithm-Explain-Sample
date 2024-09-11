/**
 * @file custom hashmap.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-09-10
 * @copyright Copyright (c) 2024
 * @problem: https://cses.fi/problemset/task/1642
 * @approach: greedy with hashmap
 * @explanation:https://usaco.guide/gold/hashmaps#:~:text=%C2%A00/2-,(Optional)%20Hashmaps,Maintaining%20collections%20of%20distinct%20elements%20with%20hashing.,-Language%3A%20C
 */

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;


mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
struct chash {  /// use most bits rather than just the lowest ones
	const uint64_t C = (long long int)(2e18 * acos((long double)-1)) + 71;  // large odd number
	const int RANDOM = rng();
	long long int
	operator()(long long int x) const {  /// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
		return __builtin_bswap64((x ^ RANDOM) * C);
	}
};
template <class K, class V> using ht = gp_hash_table<K, V, chash>;


void solve(){

    int n,sum; cin >> n >> sum;
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }

    ht<int, pair<int,int>> hm;
    for(int i=n-1;i>=0;i--){
        for(int j=i-1;j>=0;j--){
            int idx = sum - v[i] - v[j];
            if(hm.find(idx) != hm.end()){
                cout << i+1 << " " << j+1 << " " << hm[idx].first+1 << " " << hm[idx].second+1 << endl;
                return;
            }
        }
        for(int j=i+1;j<n;j++) hm[v[i]+v[j]] = {i, j};
    }
    cout << "IMPOSSIBLE" << endl;

}


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int test_cases = 1;
    // cin >> test_cases;
    for(int test_case=1;test_case<=test_cases;test_case++){
        // cout << "Case " << i << ": ";
        // memset(dp,0,n*sizeof(int));
        solve();
    }
}