/**
 * @file 12.03 count_of_inversion_ordered_set.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.1
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 * @problem: count of inversion.
 * @approach: Ordered set Method.
 * @explanation:
 *              We will be using the function order_of_key(K) which returns number of elements strictly smaller than K in log N time.
 *              Size of ordered set - order_of_key(k) is inversion with that element.
 */

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
// Ordered Set Tree
#define int long long int
#define ordered_set tree<int, null_type, less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

// S.order_of_key (k) : Number of items strictly smaller than k .
// S.find_by_order(k) : K-th element in a set (counting from zero).

void solve(){

    int n; cin >> n;
    ordered_set os;
    int inv = 0;
    for(int i=0;i<n;i++){
        int x; cin >> x;
        int less = os.order_of_key(x);
        int other = os.size() - less;
        inv += other;
        os.insert(x);
    }
    cout << inv << endl;

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