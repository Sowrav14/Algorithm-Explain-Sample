
/**
 * @file 10.2 A_1.cpp
 * @author Sowrav Nath
 * @brief  MO Algorithm Practice...
 * @version 0.1
 * @date 2024-01-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */


/***
 * in this we have to answer query where ans = k * k * s;
 * where k is occurance of each s inside the range 1 <= l <= s <= r
 * test case1, query1 (1,2) = 1*1*1 + 1*1*2 = 3
 * 
 * this is the basic approach of mo algorithm time O(n2).
*/


#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
const int N = 2*1e5+10;
const int M = 1e6+10;
const int blk = sqrt(N) + 10;

class query{
    public :
        int p, l, r, block;
        query(){}
        query(int pos, int L, int R){
            p = pos;
            l = L;
            r = R;
        }

        bool operator < (query cq){        // sort according to block then r
            if(block != cq.block) return block < cq.block;
            else return r < cq.r;
         }
};

int a[N], res[N];
int freq[M];
query q[N];

int main(){
    int n,t; cin >> n >> t;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }

    for(int i=1;i<=t;i++){
        int x,y; cin >> x >> y;
        q[i] = (query(i, x, y));
    }

    sort(q+1, q+t+1);

    int prevl = 0, prevr = 0;
    int ans = 0;
    for(int i=1;i<=t;i++){
        int curl = q[i].l;
        int curr = q[i].r;
        int idx = q[i].p;
        // cout << curl << " " << curr << " " << prevl << " " << prevr << " " << ans << endl;

        while(prevr < curr){            // adding extra from right.
            ++prevr;
            int val = a[prevr];
            int c = freq[val];
            int red = c * c * val;
            freq[val]++;
            int add = freq[val] * freq[val] * val;
            ans += add - red;
        }
        while(curl < prevl){            // adding extra from left.
            --prevl;
            int val = a[prevl];
            int c = freq[val];
            int red = c * c * val;
            freq[val]++;
            int add = freq[val] * freq[val] * val;
            ans += add - red;
        }
        while(prevl < curl){
            int val = a[prevl];
            int c = freq[val];
            int red = c * c * val;
            freq[val]--;
            int add = freq[val] * freq[val] * val;
            ans += add - red;
            prevl++;
        }
        while(prevr > curr){            // removing extra from right.
            int val = a[prevr];
            int c = freq[val];
            int red = c * c * val;
            freq[val]--;
            int add = freq[val] * freq[val] * val;
            ans += add - red;
            prevr--;
        }

        res[idx] = ans;

    }

    for(int i=1;i<=t;i++){
        cout << res[i] << endl;
    }


}