
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


class query{
    public :
        int p, l, r;
        query(int pos, int L, int R){
            p = pos;
            l = L;
            r = R;
        }

        bool operator < (query temp){
            if(this->l == temp.l){
                return this->r < temp.r;
            } else {
                return this->l < temp.l;
            }
        }
};

vector<query>q;
vector<int>v;
vector<int>results;

int main(){
    int n,t; cin >> n >> t;
    results.resize(t);
    for(int i=0;i<n;i++){
        int x; cin >> x;
        v.push_back(x);
    }

    for(int i=0;i<t;i++){
        int x,y; cin >> x >> y;
        x--; y--;
        q.push_back(query(i, x, y));
    }

    sort(q.begin(), q.end());

    // for(auto i : q){
    //     cout << i.l << " " << i.r << endl;
    // }

    map<int,int>m;
    int left = q[0].l, right = q[0].r;

    for(int i=left;i<=right;i++){
        m[v[i]]++;
    }
    int ans = 0;
    for(auto i : m) ans += (i.second) * (i.second) * (i.first);
    results[q[0].p] = ans;
    // cout << q[0].p << " " << ans << endl;
    // cout << q[0].l << " " << q[0].r << " " << ans << endl;

    for(int i=1;i<t;i++){
        int l = q[i].l;
        int r = q[i].r;

        while(l > left){
            m[v[left]]--;
            left++;
        }
        if(r > right){
            while(r > right){
                right++;
                m[v[right]]++;
            }
        }
        if(r < right){
            while(r < right){
                m[v[right]]--;
                right--;
            }
        }

        int ans = 0;
        for(auto val : m){
            ans += (val.second) * (val.second) * (val.first);
        }
        results[q[i].p] = ans;

    }

    for(auto i : results){
        cout << i << endl;
    }

}