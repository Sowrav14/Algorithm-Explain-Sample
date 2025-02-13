/**
 * @file LIS Range Queries.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-12-02
 * @copyright Copyright (c) 2024
 * @topic: Lis in Range queries
 * @problem: https://www.codechef.com/problems/SEAINCR
 * @resource: https://codeforces.com/blog/entry/52726#:~:text=The%20solution%20relies%20on%20the%20fact%20that%20sum%20of%20A%5Bi%5D%20in%20the%20file%20%3C%3D10%5E6.
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e6 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;
int n, q;
int last[N]; // last occurence index of i
vector<int>g[N];    // i to j will be directly connected if a[i] < a[j] and i < j
int a[N];
vector<pair<int,int>>queries[N]; // store queries q[x] = {y, i}
int maxlis[N];  // maximum length lis ending at i.
int ans[N];
int bit[N];
// BIT for range maximum queries...
void update(int i,int val){
	while(i<=n){
		bit[i] = max(bit[i], val);
		i = i + (i & (-i));
	}
}
int query(int i){
	int ret=0;
	while(i){
		ret = max(ret, bit[i]);
		i = i - (i & (-i));
	}
	return ret;
}

void updateDAG(int cur, int val){
    if(val > maxlis[cur]){ // update where lis increases.
        for(auto nextGreat : g[cur]){
            updateDAG(nextGreat, val + 1);
        }
        maxlis[cur] = val;
        update(cur, val);
    }
}


void solve(){

    // cin >> n >> q;
    scanf("%d", &n); scanf("%d", &q);
    for(int i=0;i<=n;i++){
        last[i] = ans[i] = maxlis[i] = bit[i] = 0;
        g[i].clear();
        queries[i].clear();
    }

    for(int i=1;i<=n;i++){
        // cin >> a[i];
        scanf("%d", &a[i]);
        last[a[i]] = i;
        int prev = 0;
        for(int j=a[i]-1;j>=1;j--){ // build the DAG
            if(last[j] > prev){
                prev = last[j];
                g[last[j]].push_back(i);
            }
        }
    }

    for(int i=1;i<=q;i++){
        int x, y; /* cin >> x >> y; */
        scanf("%d", &x); scanf("%d", &y);
        queries[x].push_back({y, i});
    }

    for(int i=n;i>=1;i--){
        // start a lis with length 1;
        updateDAG(i, 1);
        for(auto qu : queries[i]){ // process queries staring here...
            int st = i;
            int en = qu.first;
            int id =qu.second;
            ans[id] = query(en);    // 1 to R as L is compressed to 1
        }
    }

    // for(int i=1;i<=q;i++) cout << ans[i] << endl;
    for(int i=1;i<=q;i++) printf("%d\n", ans[i]);
}


signed main(){
    Fast_IO()
    int t = 1;
    scanf("%d", &t);
    for(int i=1;i<=t;i++){
        // cout << "Case #" << i << ": ";
        solve();
    }
}