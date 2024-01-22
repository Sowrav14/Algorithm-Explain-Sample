/**
 * @file 12.01 count_of_inversion_BIT.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.2
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 * @problem: is counting inversion
 * @approach: Fenwick tree or BIT.
 * @explanation:
 *              let, every node of bit as element of array
 *              for each a[i] calculate occurance of (a[i]+1, max_element)
 *              this calculated value is inversion for that a[i]
 *              calculate inversion for each element of a and sum then.
 * 
 *              a[] = {8,4,2,1}
 *              bit[] = {0, 0, 0, 0, 0, 0, 0, 0}
 *              a[1] = 8 -> bit[9, 8] = 0   inv += 0
 *              bit[] = {0, 0, 0, 0, 0, 0, 0, 1}
 *              a[2] = 4 -> bit[5, 8] = 1   inv += 1;
 *              bit[] = {0, 0, 0, 1, 0, 0, 0, 1}
 *              a[3] = 2 -> bit[3,8] = 2    inv += 2
 *              bit[] = {0, 1, 0, 1, 0, 0, 0, 1}
 *              a[4] = 1 -> bit[2,8] = 3    inv += 3
 *              bit[] = {1, 1, 0, 1, 0, 0, 0, 1}
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
int n;
vector<int>bit;

// updating val in idx;
void update(int idx, int val){
    while(idx <= n){
        bit[idx] += val;
        idx += (idx) & (-idx);
    }
}

// sum from [1...idx]
int query(int idx){
    int sum = 0;
    while(idx > 0){
        sum += bit[idx];
        idx -= (idx) & (-idx);
    }
    return sum;
}

void solve(){

    cin >> n;
    bit.resize(n+10);
    int inv = 0;
    for(int i=0;i<n;i++){
        int x; cin >> x;
        // sum from [1...n] - [1...x-1]
        // cout << query(n) - (x-1 > 0 ? query(x-1) : 0) << " ";
        inv += query(n) - (x-1 > 0 ? query(x-1) : 0);
        // updating bit of current element by 1.
        update(x, 1);
    }
    cout << inv << endl;
    bit.clear();
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