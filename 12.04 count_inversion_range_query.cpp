/**
 * @file 12.04 count_inversion_range_query.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.1
 * @date 2024-01-23
 * @copyright Copyright (c) 2024
 * @problem: count inversion in range with update queries.
 *          Sherlock and Inversions(Hackerearth).
 * @approach: MO algorithm (offline query).
 * @explanation:
 *              formal idea is to use bit(nlogn) and mo(n*sqrt(n)) 
 *              tracning [prevl, prevr]
 *              current [curl, curr]
 *              when a element x is added in left (curl < prevl) inversion increased query(1, x-1) i.e. smaller numbers occured in right.
 *              when a element x in added in right (curr > prevr) inversion increased query(x+1, n) i.e. bigger element occured in left.
 *              when a element x is removed from left (curl > prevl) inversion decreased query(1, x-1) i.e. smaller numbers occured in right.
 *              when a element x in removed from right (curr < prevr) inversion decreased query(x+1, n) i.e. bigger element occured in left.
 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
// Ordered Set Tree
#define int long long int
#define ordered_set tree<int, null_type, less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int blk = sqrt(N) + 1;

// for offline processing of query...
class offline{

    public :
         int l,r,id,block;
         offline() {}
         offline(int l, int r, int id){
            this->l = l;
            this->r = r;
            this->id = id;
            this->block = l/blk;
         }

         bool operator < (offline cq){
            if(block != cq.block) return block < cq.block;
            else return r > cq.r;
         }

};



int a[N], ans[N];
offline query[M];
int bit[N];
ordered_set os;

// updating val in idx;
void update(int idx, int val){
    while(idx < N){
        bit[idx] += val;
        idx += (idx) & (-idx);
    }
}

// sum from [1...idx]
int getsum(int idx){
    int sum = 0;
    while(idx > 0){
        sum += bit[idx];
        idx -= (idx) & (-idx);
    }
    return sum;
}

void solve(){

    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        os.insert(a[i]);
    }
    // mapping the values to neglect large numbers.
    for(int i=1;i<=n;i++){
        a[i] = os.order_of_key(a[i]) + 1;
    }

    for(int i=1;i<=q;i++){
        int x,y; cin >> x >> y;
        query[i] = offline(x, y, i);
    }
    
    sort(query+1, query+q+1);
    int prevl = 1, prevr = 0;
    int inv = 0;
    for(int i=1;i<=q;i++){
        int curl = query[i].l;
        int curr = query[i].r;
        int idx = query[i].id;

        // adding element from left...
        // inversion will increased by no of smaller elements ( bit[1...x-1]) of that elements.
        while(curl < prevl){
            prevl--;
            int x = a[prevl];
            inv += getsum(x-1);
            update(x, 1);
        }
        // adding element from right.
        // inversions will increased by no of bigger elements (bit[x+1...N]) of that element
        while(curr > prevr){
            prevr++;
            int x = a[prevr];
            int all = getsum(N-5);
            int nth = getsum(x);
            inv += all - nth;
            update(x, 1);
        }
        // removing element from left.
        // inversion decreased by no of element smaller (bit[1...x-1]) of that element.
        while(curl > prevl){
            int x = a[prevl];
            inv -= getsum(x-1);
            update(x, -1);
            prevl++;
        }
        // removing element from right...
        // inversions will decreased by no of element bigger(bit[x+1...N])
        while(curr < prevr){
            int x = a[prevr];
            int all = getsum(N-5);
            int nth = getsum(x);
            inv -= all - nth;  
            update(x, -1);          
            prevr--;
        }
        ans[idx] = inv;
    }

    for(int i=1;i<=q;i++) cout << ans[i] << endl;
   
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