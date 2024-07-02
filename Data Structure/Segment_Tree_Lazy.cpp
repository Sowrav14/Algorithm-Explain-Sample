#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5 + 10;
int a[N];

// Structuring Segment Tree...
struct SegmentTree {
  	#define lc (n << 1)
	#define rc ((n << 1) | 1)
	int tree[4 * N], lazy[4 * N];
	SegmentTree() {
		memset(tree, 0, sizeof tree);
		memset(lazy, 0, sizeof lazy);
	}
	// push the lazy value toward leafs...
	inline void push(int n, int b, int e) {
		if (lazy[n] == 0) return;
        // check here how to update lazy...
		tree[n] = tree[n] + lazy[n];
		if (b != e) {
    		lazy[lc] = lazy[lc] + lazy[n];
    		lazy[rc] = lazy[rc] + lazy[n];
		}
		lazy[n] = 0;
	}
	// combine two node of segment tree... how??
	inline int combine(int a,int b) {
		return max(a, b);
	}
	inline void pull(int n) {
		tree[n] = max(tree[lc], tree[rc]);
	}
	// building the segment tree...
	void build(int n, int b, int e) {
		lazy[n] = 0;
		if (b == e) {
    		tree[n] = a[b];
    		return;
		}
		int mid = (b + e) >> 1;
		build(lc, b, mid);
		build(rc, mid + 1, e);
		pull(n);
	}
	// Updating range...
	void update(int n, int b, int e, int i, int j, int v) {
		push(n, b, e);
		if (j < b || e < i) return;
		if (i <= b && e <= j) {
    		lazy[n] = v; //set lazy
    		push(n, b, e);
    		return;
    	}
		int mid = (b + e) >> 1;
		update(lc, b, mid, i, j, v);
		update(rc, mid + 1, e, i, j, v);
		pull(n);
	}
	// range query...
	int query(int n, int b, int e, int i, int j) {
		push(n, b, e);
		if (i > e || b > j) return -1e18;	// what??
		if (i <= b && e <= j) return tree[n];
		int mid = (b + e) >> 1;
		return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
	}
};


void solve(){

    int n,q; cin >> n >> q;
	vector<int>v(n+10, 0);
	for(int i=1;i<=n;i++){
		cin >> v[i];
		a[i] = a[i-1] + v[i];
	}

	SegmentTree temp;
	temp.build(1, 1, n);
	while(q--){
		int t, i, j; cin >> t >> i >> j;
		if(t == 2){
			cout << max(0ll, temp.query(1, 1, n, i, j) - (i == 1 ? 0 : temp.query(1, 1, n, i-1, i-1))) << endl;
		} else{
			int val = j - v[i];
			temp.update(1, 1, n, i, n, val);
            v[i] = j;
		}
	}

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